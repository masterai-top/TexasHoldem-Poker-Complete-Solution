#pragma once

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void TokenTo(GameRoot *root);
            void SortCidBySmallCid(GameRoot *root, std::vector<int>& vecCids);
            void SimpleNewAct(GameRoot *root, int cid);
        }
    }
}

