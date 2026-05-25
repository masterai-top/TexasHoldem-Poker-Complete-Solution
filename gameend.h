#pragma once

namespace XTimer
{
    class TimerParam;
}

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void GameEnd(GameRoot *root);

            int GameClear(XTimer::TimerParam & param);

            //取淘汰用户
            vector<long> getDisuseUin(GameRoot *root);

            int sendGameFinish2Room(GameRoot *root);
        }
    }
}

