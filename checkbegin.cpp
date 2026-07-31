#include "Comm/ITableGame.h"
#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/gamelogic/core/checkbegin.h"
#include "message/sendroommessage.h"
#include "logic/gamelogic/core/begintimer.h"
#include "logic/gamelogic/core/endtimer.h"
#include "utils/tarslog.h"
#include "context/context.h"
#include "config/gameconfig.h"
#include "process/process.h"
#include "CommonCode.pb.h"
#include "message/sendclientmessage.h"
#include "ddz.pb.h"

using namespace nndef;

namespace game
{
    namespace logic
    {
        namespace gamelogic
        {
            using namespace context;
            using namespace process;
            using namespace gamelogic;
            using namespace config;
            using namespace nninvalid;
            using namespace RoomSo;
            using namespace message;

            int CheckBegin(GameRoot *root)
            {
                bool allReadyFlag = true;
                std::map<cid_t, User> &usermap = root->con->refUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                {
                    DLOG_TRACE("roomid:" << root->roomid() << ", checkbegin cid" << it->first << ", uid: "<< it->second.getUid() << ", ready: "<< it->second.isReady());
                    if (!it->second.isReady())
                    {
                        allReadyFlag = false;
                        break;
                    }
                }

                if(usermap.size() == 3 && allReadyFlag && root->pro->getProcess() == nil_nnstate)//开始游戏
                {
                    DLOG_TRACE("roomid:" << root->roomid() << ", user size: "<< usermap.size() << ", game begin flag: "<< root->con->isGameBegin() );
                    if(!root->con->isGameBegin())
                    {
                        //推送房间游戏开始
                        TGAME_GameBegin tmBegin;
                        sendRoomMessage<TGAME_GameBegin>(TGAME_GameBegin_E, tmBegin, root);
                        root->con->setGameBegin(true);
                        root->con->setBeginTime(time(nullptr));
                        
                        EndTimer(NN_XTIME_KILL_ALL, root, false);
                        EndTimer(NN_XTIME_GAME_XTIME, root, false);
                        BeginTimer(NN_XTIME_GAME_XTIME, 1, [](TimerParam & param)->int
                        {
                            auto body = static_cast<std::tuple<GameRoot *> const *>(param.getBody());
                            auto root = std::get<0>(*body);

                            root->pro->turnProcess(NN_STATE_SEND_CARD);
                            return 0;
                        }, root, false); 

                        root->con->clearCalInfo();
                    }           
                }
                return 0;
            }
        }
    }
}
