#include "common/macros.h"
#include "gameroot.h"
#include "logic/gamelogic/core/begintimer.h"
#include "utils/tarslog.h"
#include "dz.pb.h"
#include "message/sendclientmessage.h"

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            void BeginTimer(E_NN_XTIME xtimekey, int time, std::function<int(TimerParam &)> func, GameRoot *root, bool toclient)
            {
                __TRY__

                DLOG_TRACE("roomid:" << root->roomid() << ", " << "@BeginTimer, time key: " << xtimekey << ", time: " << time << ", roomid:" << root->roomid());

                Aggr::getInstance()->kill(root->roomid(), xtimekey);
                Aggr::getInstance()->addXid(root->roomid(), xtimekey, SetSoTimer<std::tuple<GameRoot *>>(make_tuple(root), func, xtimekey, time, 0));

                if (toclient)
                {
                    using namespace message;

                    //通知客户端
                    XGameDZProto::NN_msg2sTimerBegin nncm;
                    nncm.set_itime(time);
                    nncm.set_ixtkey(xtimekey);
                    sendAllClientMessage<XGameDZProto::NN_msg2sTimerBegin>(XGameDZProto::NN_msg2sTimerBegin_E, nncm, root);
                }

                __CATCH__
            }
        }
    }
}
