#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            int LeaveDesk(GameRoot *root, bool bTimeOut = false);
            int RemoveUser(GameRoot *root, std::vector<long> vdelUser);
        }
    }
}

