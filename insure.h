#pragma once

namespace game
{
    class GameRoot;

    namespace logic
    {
        namespace gamelogic
        {
            // (在用)
            bool CheckInsureHehe(GameRoot *root);

            //
            bool CheckPool(GameRoot *root);

            // (在用)
            bool CheckPoolHaha(GameRoot *root);
            // (在用)
            void CheckOuts(GameRoot *root, std::map<cid_t, long> mapBetPool, int iIndex, long lPool, long lUid);

            void InsureNoticeHehe(GameRoot *root);

            // (在用)
            void InsureNoticeHaha(GameRoot *root);

            void InsureHehe(GameRoot *root, int ret, long uId);

            // (在用)
            void InsureHaha(GameRoot *root, int ret, long uId);

            // 判定是否触发保险
            bool CheckInsure(GameRoot *root);

            void InsureNotice(GameRoot *root);

            void Insure(GameRoot *root, int ret, long uId);

            long GetInsurePool(GameRoot * root, const long cid1, const long cid2);

            // (在用)
            int Complete(E_NN_TYPE typeOne, E_NN_TYPE typeTwo, int iGameType);

            // (在用)
            void PrintCards(std::stringstream &cardStr, vecc_t &cards);
        }
    }
}