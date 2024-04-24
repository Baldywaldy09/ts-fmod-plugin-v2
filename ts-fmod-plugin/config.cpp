#include "../pch.h"
#include "config.h"

config::config(const scs_log_t scs_log, const std::filesystem::path& config_file_path) : scs_log_(scs_log),
    config_path_(config_file_path)
{
}

template <typename T>
bool config::read_value(const json& j, const char* key, T* out_value) const
{
    try
    {
        *out_value = j[key].get<T>();
    }
    catch (...)
    {
        std::stringstream ss;
        ss << "[ts-fmod-plugin-v2] Could not read config value '" << key << "', using default value '" << *out_value <<
            "'";
        scs_log_(SCS_LOG_TYPE_error, ss.str().c_str());
        return false;
    }

    return true;
}

bool config::load_config()
{
    if (!exists(config_path_))
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin-v2] Could not find the 'sound_levels.txt' file");
        return false;
    }

    std::ifstream sound_levels_file(config_path_);
    std::string line;

    if (!sound_levels_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin-v2] Could not read the 'sound_levels.txt' file");
        return false;
    }

    json j;

    try
    {
        sound_levels_file >> j;
    }
    catch (json::parse_error&)
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin-v2] Could not parse JSON from 'sound_levels.txt'");
        return false;
    }

    if (
        !read_value(j, "Master", &master) ||
        !read_value(j, "Navigation", &navigation) ||
        !read_value(j, "Menu_Music", &menu_music) ||
        !read_value(j["Truck"], "Engine", &engine) ||
        !read_value(j["Truck"], "Exhaust", &exhaust) ||
        !read_value(j["Truck"], "Turbo", &turbo) ||
        !read_value(j["Interior"], "Interior_Sounds", &interior_buttons) ||
        !read_value(j["Interior"], "Engine_Volume_When_Windows_Closed", &windows_closed))
    {
        scs_log_(SCS_LOG_TYPE_warning,
            "[ts-fmod-plugin-v2] Found an incorrect setting in 'sound_levels.txt' file, resetting its value to default");
        save_config();
    }


    return true;
}

bool config::save_config()
{
    scs_log_(SCS_LOG_TYPE_message, "[ts-fmod-plugin-v2] Saving the 'sound_levels.txt' file...");

    std::ofstream sound_levels_file(config_path_, std::ios::trunc);

    if (!sound_levels_file.is_open())
    {
        scs_log_(SCS_LOG_TYPE_error, "[ts-fmod-plugin-v2] Could not open the 'sound_levels.txt' file to write to.");
        return false;
    }

    const nlohmann::ordered_json j = {
        {"Master", master},
        {"Navigation", navigation},
        {"Menu_Music", menu_music},
        {"Truck", {
            {"Engine", engine},
            {"Exhaust", exhaust},
            {"Turbo", turbo}
        }},
        {"Interior", {
            {"Engine_Volume_When_Windows_Closed", windows_closed},
            {"Interior_Sounds", interior_buttons}
        }}
    };

    sound_levels_file << j.dump(4);
    sound_levels_file.close();

    return true;
}
