#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/clientlogic/core/tokenbet.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/endtimer.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/tokento.h"
#include "logic/gamelogic/core/autobet.h"
#include "logic/timeoutlogic/core/bettimeout.h"
#include "config/gameconfig.h"

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            int Defer(GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "Defer");

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace gamelogic;
                using namespace config;
                using namespace timeoutlogic;

                //
                cid_t tokencid = root->con->getTokenCid();
                User *user = root->con->getUserByCid(tokencid);
                if (user == NULL)
                {
                    DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "getUserByCid null, tokencid: " << tokencid);
                    return -1;
                }

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", time:" << root->cfg->timestamp() << ", uid:" << user->getUid());

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "Defer, flag: " << user->getProlongFlag());
                BetTimeOut(root);

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", time:" << root->cfg->timestamp() << ", uid:" << user->getUid());

                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
