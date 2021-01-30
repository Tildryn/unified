#pragma once

#include "Common.hpp"
#include "Services/Hooks/Hooks.hpp"

namespace Events {

class CombatEvents
{
public:
    CombatEvents(NWNXLib::Services::HooksProxy* hooker);

private:
    static void StartCombatRoundHook(CNWSCombatRound*, ObjectID);
    static int32_t ApplyDisarmHook(CNWSEffectListHandler*, CNWSObject *, CGameEffect *, BOOL);
    static int32_t SendServerToPlayerAmbientBattleMusicPlayHook(CNWSMessage*, PlayerID oidPlayer, BOOL bPlay);
};

}
