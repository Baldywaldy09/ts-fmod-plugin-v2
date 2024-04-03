// core.h
#pragma once

#include "telemetry_data.h"
#include "fmod_manager.h"
#include <vector>

namespace hooks
{
    class hook;
}

class core
{
    scs_log_t scs_log_;
    fmod_manager* fmod_manager_instance_;
    std::vector<hooks::hook*> installed_hooks_;

public:
    static core* g_instance;

    core(const scs_log_t scs_log, fmod_manager* fmod_manager_instance);
    ~core();
    bool init();
    void tick();
    void uninitialize() const;

    void log(scs_log_type_t log_type, scs_string_t message) const;
    fmod_manager* get_fmod_manager() const; // Changed function name to avoid conflict
};
