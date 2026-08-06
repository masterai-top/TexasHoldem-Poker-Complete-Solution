#include "common/macros.h"
#include "gameroot.h"
#include "Comm/ITableGame.h"
#include "utils/tarslog.h"
#include "message/sendclientmessage.h"
#include "message/sendroommessage.h"
#include "config/gameconfig.h"
#include "dz.pb.h"
#include "logic/clientlogic/core/tokenbet.h"
#include "context/context.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/endtimer.h"

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int AIDecide(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace context;
                using namespace RoomSo;
                using namespace message;
                using namespace gamelogic;

                TGAME_AIDecide const *nnrs = static_cast<TGAME_AIDecide const *>(p);
                if(nnrs == nullptr)
                {
                    return -1;
                }

                // for test

                DLOG_TRACE("roomid:"<<root->roomid()<<", AIDecide. uid: "<< nnrs->uid <<", type: "<< nnrs->type << ", betNum: "<< nnrs->betNum);

                if(nnrs->err_msg != "Succ")
                {
                    DLOG_ROBOT("roomid: "<< root->roomid() << ", err_msg: "<< nnrs->err_msg);
                }

                std::vector<long> vbet_action;
                vbet_action.push_back(nnrs->uid);
                vbet_action.push_back(nnrs->type);
                vbet_action.push_back(nnrs->betNum);
                vbet_action.push_back(nnrs->action_num);
                root->con->setAiBetAction(vbet_action);

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
