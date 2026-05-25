#pragma once

#include<vector>

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            int CheckBegin(GameRoot *root);
            int CheckBeginQS(GameRoot *root, std::vector<long>& vecStandUid, std::vector<long>& vecStandTailUid);
            void SendPauseGameInfo(GameRoot *root, long uid = 0);
            void SendUpdateApplyed(GameRoot *root, long uid);
            int DingZhuang(GameRoot *root, int iModel = 0);
        }
    }
}

