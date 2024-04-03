#pragma once
#include "hook.h"

namespace prism
{
    struct sound_event_t;
}

// .text:00000001401AB590; char __fastcall fmod::maybe_event_update(prism::sound_event_t* a1, bool stop, __int64 a3)
using prism_sound_event_update = bool __fastcall(
    const prism::sound_event_t* sound_event,
    bool stop,
    int64_t a3
);

extern bool start_bad;

namespace hooks
{
    class sound final : public hook
    {
        prism_sound_event_update* sound_event_update_ = nullptr;

    public:
        /**
         * \brief Installs the console hook
         * \return True if successfully hooked the cmd_execute function
         */
        bool install() override;
        void uninstall() override;
    };
}
