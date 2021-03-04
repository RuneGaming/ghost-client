#include "Init.hpp"

#include "module.h"
#include "aimassist.hpp"
#include "antibot.hpp"
#include "velocity.hpp"

static void InitializeModules()
{
    //modules.push_back(std::make_unique<AntiBot>());
    //modules.push_back(std::make_unique<AimAssist>());
}

std::vector<HANDLE> threads;
std::vector<HANDLE> getThreads()
{
	return threads;
}

void Initialize()
{
    for (const auto& module : modules) {
        //threads.push_back(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)module->onUpdate, NULL, 0, 0));

    }
}
