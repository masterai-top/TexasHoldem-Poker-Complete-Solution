#include "common/macros.h"
#include "gameroot.h"
#include "logic/gamelogic/core/autobet.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "logic/gamelogic/core/tokento.h"
#include "logic/clientlogic/core/tokenbet.h"
#include "common/nndef.h"
#include "xtime4lib.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            void AutoFold(GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                DLOG_TRACE("roomkey:" << root->cfg->getRoomKey() << ", " << "AutoFold");

                using namespace context;
                using namespace process;
                using namespace message;
                using namespace config;
                using namespace clientlogic;

                cid_t tokencid = root->con->getTokenCid();
                User *user = root->con->getUserByCid(tokencid);

                XGameDZProto::NN_msg2cTokenBet nncm;
                nncm.set_idzact(NN_ACT_FOLD);
                nncm.set_lbetnum(0);

                vector<char> vecOutBuffer;
                pbTobuffer(nncm, vecOutBuffer);
                clientlogic::TokenBet(user->getUid(), vecOutBuffer, root);

                __CATCH__
                PERFSTATS_EXIT();
            }
        }
    }
}
