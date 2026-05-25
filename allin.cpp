#include "common/macros.h"
#include "gameroot.h"
#include "logic/gamelogic/core/allin.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/endtimer.h"
#include "common/nndef.h"
#include "xtime4lib.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            void AllIn(GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "AllIn");

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace config;

                XGameDZProto::NN_msg2sShowHdCard nncm;
                auto usermap = root->con->getUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                {
                    if (!it->second.isMidSit() && !it->second.isFold())
                    {
                        XGameDZProto::NN_msg2sShowHdCard_NN_hdCard nnhdcard;
                        for (auto itcards = it->second.getVecCards().begin(); itcards != it->second.getVecCards().end(); ++itcards)
                        {
                            nnhdcard.add_hdcard(*itcards);
                        }

                        (*nncm.mutable_mhdcard())[it->first] = nnhdcard;
                    }
                }

                //推送手牌
                sendAllClientMessage<XGameDZProto::NN_msg2sShowHdCard>(XGameDZProto::NN_msg2csShowHdCard_E, nncm, root);

                //全押操作
                root->con->setInAllIn(true);
                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "begintimer, timer id = " << NN_XTIME_WAIT_SPACE << ", time : " << root->cfg->getDelayTime());
                EndTimer(NN_XTIME_WAIT_SPACE, root, false);
                BeginTimer(NN_XTIME_WAIT_SPACE, root->cfg->getDelayTime(), [](TimerParam & param)->int
                {
                    auto body = static_cast<std::tuple<GameRoot *> const *>(param.getBody());
                    auto root = std::get<0>(*body);
                    DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "begintimer, timer id = " << NN_XTIME_WAIT_SPACE);
                    root->pro->nextProcess();
                    return 0;
                }, root, false);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
