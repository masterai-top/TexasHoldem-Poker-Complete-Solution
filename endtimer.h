#pragma once

#include "common/nndef.h"

using namespace nndef;

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void EndTimer(E_NN_XTIME xtimekey, GameRoot *root, bool toclient = true);
        }
    }
}

