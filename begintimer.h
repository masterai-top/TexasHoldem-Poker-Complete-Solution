#pragma once

#include "common/nndef.h"
#include "xtime4lib.h"

using namespace nndef;

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void BeginTimer(E_NN_XTIME xtimekey, int time, std::function<int(TimerParam &)> func, GameRoot *root, bool toclient = true);
        }
    }
}

