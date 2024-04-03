#pragma once
#include "../pch.h"
#include <cstdint>
#include <sstream>
#include <Windows.h>
#include <vector>

namespace memory
{
    // Ripped from an old GTA project I used to use
    // https://bitbucket.org/gir489/m0d-s0beit-v-redux/src/master/m0d-s0beit-v/Pattern.h
    struct pattern_byte
    {
        pattern_byte() : ignore(true)
        {
            //
        }

        explicit pattern_byte(const std::string& byte_string, const bool ignore_this = false) : ignore(ignore_this),
                                                                                                data(string_to_uint8(byte_string))
        {
        }

        bool ignore;
        uint8_t data;

    private:
        static uint8_t string_to_uint8(const std::string& str)
        {
            std::istringstream iss(str);

            uint32_t ret;

            if (iss >> std::hex >> ret)
            {
                return static_cast<uint8_t>(ret);
            }

            return 0;
        }
    };

    struct pattern
    {
        static uint64_t scan(const std::string s, const uint64_t start, const uint64_t length)
        {
            std::vector<pattern_byte> p;
            std::istringstream iss(s);
            std::string w;

            while (iss >> w)
            {
                if (w[0] == '?')
                {
                    // Wildcard
                    p.emplace_back();
                }
                else if (w.length() == 2 && isxdigit(w[0]) && isxdigit(w[1]))
                {
                    // Hex
                    p.emplace_back(w);
                }
                else
                {
                    return NULL;
                }
            }

            for (uint64_t i = 0; i < length; i++)
            {
                auto current_byte = reinterpret_cast<uint8_t*>(start + i);

                auto found = true;

                for (size_t ps = 0; ps < p.size(); ps++)
                {
                    if (p[ps].ignore == false && current_byte[ps] != p[ps].data)
                    {
                        found = false;
                        break;
                    }
                }

                if (found)
                {
                    return reinterpret_cast<uint64_t>(current_byte);
                }
            }

            return NULL;
        }
    };

    inline uint64_t get_address_for_pattern(const char* pattern, const uint64_t offset = 0)
    {
        thread_local static bool initialized = false;
        thread_local static uintptr_t game_base = 0;
        thread_local static uint32_t img_size = 0;

        if (!initialized)
        {
            game_base = reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr));
            const auto header = reinterpret_cast<const IMAGE_DOS_HEADER*>(game_base);
            const auto nt_header = reinterpret_cast<const IMAGE_NT_HEADERS64*>(
                reinterpret_cast<const uint8_t*>(header) + header->e_lfanew);
            img_size = nt_header->OptionalHeader.SizeOfImage;
            initialized = true;
        }

        return pattern::scan(
            pattern,
            game_base,
            img_size) + offset;
    }

    inline uint64_t get_address_with_offset(const uint64_t offset)
    {
        return reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)) + offset - 0x140000000;
    }

    template <class T>
    T* get_function_with_offset(const uint64_t offset)
    {
        return reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(GetModuleHandleA(nullptr)) + offset - 0x140000000);
    }

    template <class T>
    T* get_function_address(const char* pattern, const uint64_t offset = 0)
    {
        const auto address = get_address_for_pattern(pattern);

        if (address == 0)
        {
            return nullptr;
        }

        return reinterpret_cast<T*>(address + offset);
    }

    template <class T>
    T* get_vtable_function(const uint64_t vtable_address, const uint64_t offset)
    {
        return reinterpret_cast<T*>(*reinterpret_cast<uint64_t*>(vtable_address + offset * 0x08));
    }
}
