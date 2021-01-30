#pragma once

#include "Common.hpp"
#include "Services/Hooks/Hooks.hpp"

namespace Tracking {

class Activity
{
public:
    Activity(NWNXLib::Services::MetricsProxy* metrics, NWNXLib::Services::HooksProxy* hooks);

private:
    static int32_t MainLoopUpdate(CServerExoAppInternal*);
};

}
