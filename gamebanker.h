#pragma once

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            void GameBankerCommon(GameRoot *root);
            void GameBanker(GameRoot *root);
            void GameBankerForShortDeck(GameRoot *root);
        }
    }
}

