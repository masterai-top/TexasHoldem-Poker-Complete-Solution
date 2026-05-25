#pragma once

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            // 判定是否触发跑马
            bool CheckPaoma(GameRoot *root);

            // 跑马通知
            void PaomaNotice(GameRoot *root);

            // 跑马申请
            void PaomaApply(GameRoot *root, long uId, int count);

            // 跑马应答
            void PaomaAnswer(GameRoot *root, long uId, int agree);

            // 跑马发牌
            void PaomaShowCard(GameRoot *root);

            // 跑马工具操作
            void PaomaNext(GameRoot *root);
        }
    }
}