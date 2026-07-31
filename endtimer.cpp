#include "common/macros.h"
#include "gameroot.h"
#include "logic/gamelogic/core/endtimer.h"
#include "utils/tarslog.h"
#include "dz.pb.h"
#include "process/process.h"
#include "message/sendclientmessage.h"
#include "xtime4lib.h"

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            void EndTimer(E_NN_XTIME xtimekey, GameRoot *root, bool toclient)
            {
                __TRY__

                DLOG_TRACE("roomid:" << root->roomid() << ", " << "@EndTimer, timekey: " << xtimekey << ", time: " << time << ", roomid:" << root->roomid());

                //
                if (xtimekey == NN_XTIME_KILL_ALL)
                {
                    Aggr::getInstance()->kill(root->roomid());
                }
                else
                {
                    Aggr::getInstance()->kill(root->roomid(), xtimekey);
                }

                //
                if (toclient)
                {
                    using namespace message;

                    //通知客户端
                    XGameDZProto::NN_msg2csDefault nncm;
                    sendAllClientMessage<XGameDZProto::NN_msg2csDefault>(XGameDZProto::NN_msg2sTimerEnd_E, nncm, root);
                }

                __CATCH__
            }
        }
    }
}
