#include "common/macros.h"
#include "gameroot.h"
#include "logic/gamelogic/core/autobet.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "common/nndef.h"
#include "xtime4lib.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            void AutoBet(GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "AutoBet");

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace config;

                std::map<cid_t, User> const &usermap = root->con->getUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                {
                    if (!it->second.isMidSit() && !it->second.isFold() && !it->second.isAllIn())
                    {
                        XGameDZProto::NN_msg2sAutoBet nncm;
                        nncm.set_lbetnum(root->con->getMinBetNum() - root->con->getUserBetNum(it->first));
                        if (nncm.lbetnum() > it->second.getDZWealth())
                        {
                            nncm.set_lbetnum(it->second.getDZWealth());
                        }

                        sendClientMessage<XGameDZProto::NN_msg2sAutoBet>(it->second.getUid(), XGameDZProto::NN_msg2sAutoBet_E, nncm, root);
                    }
                }

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
