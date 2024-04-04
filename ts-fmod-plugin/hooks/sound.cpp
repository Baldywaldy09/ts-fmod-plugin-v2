#include "../pch.h"
#include "sound.h"
#include "MinHook.h"
#include "../core.h"
#include "../prism/sound.h"
#include <scssdk/scssdk.h>
#include "../utils/memory.h"
#include "../fmod_manager.h"

using namespace std;

namespace hooks
{
    prism_sound_event_update* original_sound_event_update = nullptr;
    scs_log_t scs_log;

    string allowedEvents = "interior/noise | engine/engine | engine/exhaust | engine/turbo | engine/start_bad | interior/air_warning | interior/blinker_on | interior/blinker_off | interior/stick_blinker | interior/stick_blinker_off | interior/stick_park_brake | interior/stick_park_brake_off | interior/stick_retarder | interior/stick_hazard_warning | interior/stick_high_beam | interior/stick_light_horn | interior/stick_lights | interior/stick_wipers | interior/window_move | interior/window_click | and_then_exit_left | and_then_exit_right | and_then_go_straight | and_then_keep_left | and_then_keep_right | and_then_turn_left | and_then_turn_right | compound_exit_left | compound_exit_right | compound_go_straight | compound_keep_left | compound_keep_right | compound_turn_left | compound_turn_right | exit_left | exit_now | exit_right | finish | go_straight | keep_left | keep_right | prepare_exit_left | prepare_exit_right | prepare_turn_left | prepare_turn_right | recomputing | roundabout_1 | roundabout_2 | roundabout_3 | roundabout_4 | roundabout_5 | roundabout_6 | speed_signal | speed_warning | start | turn_left | turn_right | u_turn |";
    string customEvents = "engine/start_bad | interior/noise | effects/air_brake | effects/air_cutoff |"; // sounds that the plugin needs to play from here:
    string whenStopped = "interior/noise |"; // sounds that should play only when last one has stopped playing

    bool detoured_sound_event_update(prism::sound_event_t* sound_event, const bool stop, const int64_t a3)
    {
        string soundRef = sound_event->soundref_content.str.c_str;
        string event;
        size_t pos = soundRef.find('#');
        if (pos != string::npos) {
            event = soundRef.substr(pos);
            event = event.erase(0, 1);
        }


        // Mutes custom sounds //
        // TODO: Make it check if the custom sound was registed //
        if (allowedEvents.find(event + " |") != string::npos) sound_event->volume = 0;

        // Play the sound //
        if (customEvents.find(event + " |") != string::npos)
        {
            // Check if it should only play when stopped //
            bool condition = (whenStopped.find(event + " |") != string::npos);
            core::g_instance->get_fmod_manager()->set_event_state(event.c_str(), true, condition);


            // Needed to stop other engine sounds playing //
            if (event == "engine/start_bad") start_bad = true;
        }

        return original_sound_event_update(sound_event, stop, a3);
    }

    bool sound::install()
    {
        sound_event_update_ = memory::get_function_address<prism_sound_event_update>(
            "4C 8B DC 49 89 6B 20 57 48 83 EC 70 8B 41 2C 0F B6 EA 48 8B F9");

        if (sound_event_update_ == nullptr)
        {
            core::g_instance->log(SCS_LOG_TYPE_error,
                                  "[sound::install] Could not find address for 'sound_event_update'");
            return false;
        }

        if (MH_CreateHook(reinterpret_cast<LPVOID>(sound_event_update_),
                          &detoured_sound_event_update,
                          reinterpret_cast<LPVOID*>(&original_sound_event_update)) != MH_OK)
        {
            core::g_instance->log(SCS_LOG_TYPE_error, "[sound::install] Could not create 'sound_event_update' hook");
            return false;
        }

        if (MH_EnableHook(reinterpret_cast<LPVOID>(sound_event_update_)) != MH_OK)
        {
            core::g_instance->log(SCS_LOG_TYPE_error, "[sound::install] Could not enable 'sound_event_update' hook");
            return false;
        }
        installed_ = true;
        return true;
    }

    void sound::uninstall()
    {
        if (!installed_) return;
        if (MH_DisableHook(reinterpret_cast<LPVOID>(sound_event_update_)) != MH_OK)
        {
            core::g_instance->log(SCS_LOG_TYPE_error, "[sound::uninstall] Could not disable 'sound_event_update' hook");
            return;
        }

        if (MH_RemoveHook(reinterpret_cast<LPVOID>(sound_event_update_)) != MH_OK)
        {
            core::g_instance->log(SCS_LOG_TYPE_error, "[sound::uninstall] Could not remove 'sound_event_update' hook");
            return;
        }
        installed_ = false;
    }
}
