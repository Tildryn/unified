#include "Events/LevelEvents.hpp"
#include "API/CNWSCreature.hpp"
#include "API/CNWSCreatureStats.hpp"
#include "API/Functions.hpp"
#include "Events.hpp"

namespace Events {

using namespace NWNXLib;
using namespace NWNXLib::API;
using namespace NWNXLib::Services;

static Hooking::FunctionHook *s_LevelUpHook;
static Hooking::FunctionHook *s_LevelUpAutomaticHook;
static Hooking::FunctionHook *s_LevelDownHook;

LevelEvents::LevelEvents(HooksProxy* hooker)
{
    Events::InitOnFirstSubscribe("NWNX_ON_LEVEL_UP_.*", [hooker]() {
        s_LevelUpHook = hooker->Hook(API::Functions::_ZN17CNWSCreatureStats7LevelUpEP13CNWLevelStatshhhi,
                                     (void*)&LevelUpHook, Hooking::Order::Earliest);
    });
    Events::InitOnFirstSubscribe("NWNX_ON_LEVEL_UP_AUTOMATIC_.*", [hooker]() {
        s_LevelUpAutomaticHook= hooker->Hook(API::Functions::_ZN17CNWSCreatureStats16LevelUpAutomaticEhih,
                                             (void*)&LevelUpAutomaticHook, Hooking::Order::Earliest);
    });
    Events::InitOnFirstSubscribe("NWNX_ON_LEVEL_DOWN_.*", [hooker]() {
        s_LevelDownHook = hooker->Hook(API::Functions::_ZN17CNWSCreatureStats9LevelDownEP13CNWLevelStats,
                                       (void*)&LevelDownHook, Hooking::Order::Earliest);
    });
}

void LevelEvents::LevelUpHook(CNWSCreatureStats *thisPtr, CNWLevelStats *pLevelUpStats, uint8_t nDomain1, uint8_t nDomain2,
                              uint8_t nSchool, int32_t bAddStatsToList)
{
    Events::SignalEvent("NWNX_ON_LEVEL_UP_BEFORE", thisPtr->m_pBaseCreature->m_idSelf);
    s_LevelUpHook->CallOriginal<void>(thisPtr, pLevelUpStats, nDomain1, nDomain2, nSchool, bAddStatsToList);
    Events::SignalEvent("NWNX_ON_LEVEL_UP_AFTER", thisPtr->m_pBaseCreature->m_idSelf);
}

int32_t LevelEvents::LevelUpAutomaticHook(CNWSCreatureStats *thisPtr, uint8_t nClass, int32_t bReadyAllSpells, uint8_t nPackage)
{
    Events::SignalEvent("NWNX_ON_LEVEL_UP_AUTOMATIC_BEFORE", thisPtr->m_pBaseCreature->m_idSelf);
    auto retVal = s_LevelUpAutomaticHook->CallOriginal<int32_t>(thisPtr, nClass, bReadyAllSpells, nPackage);
    Events::SignalEvent("NWNX_ON_LEVEL_UP_AUTOMATIC_AFTER", thisPtr->m_pBaseCreature->m_idSelf);
    return retVal;
}

void LevelEvents::LevelDownHook(CNWSCreatureStats *thisPtr, CNWLevelStats *pLevelUpStats)
{
    Events::SignalEvent("NWNX_ON_LEVEL_DOWN_BEFORE", thisPtr->m_pBaseCreature->m_idSelf);
    s_LevelDownHook->CallOriginal<void>(thisPtr, pLevelUpStats);
    Events::SignalEvent("NWNX_ON_LEVEL_DOWN_AFTER", thisPtr->m_pBaseCreature->m_idSelf);
}

}
