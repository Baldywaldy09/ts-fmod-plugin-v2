#pragma once
#include <cstdint>

namespace prism
{
    struct string
    {
        explicit string(const char* const s) : c_str(s)
        {
        }

        const char* c_str = nullptr;
    };

    class string_dyn_t
    {
    public:
        string str;
        uint32_t size;
        uint32_t capacity;

        virtual void func_0();
        // etc...
    };
}
