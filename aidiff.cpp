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

namespace game
{
    namespace logic
    {
        namespace roomlogic
        {
            int AIDiff(void const *p, GameRoot *root)
            {
                PERFSTATS_ENTRY();
                __TRY__

                using namespace context;
                using namespace RoomSo;
                using namespace message;

                TGAME_AIDiff const *nnrs = static_cast<TGAME_AIDiff const *>(p);
                if(nnrs == nullptr)
                {
                    return -1;
                }

                //DLOG_TRACE("roomid:"<<root->roomid()<<", diff: "<< printTars(*nnrs));

                for(auto item : nnrs->diff)
                {
                    User* user = root->con->getUserByUid(item.first);
                    if(user && user->isRobot())
                    {
                        user->setDiff(item.second);
                    }
                }
                if(root->con->getAiThinkTime() == 0)
                {
                    for(auto item : nnrs->think)
                    {
                        root->con->setAiThinkTime(item.first, item.second);
                        DLOG_TRACE("roomid:"<<root->roomid()<<", first: "<< item.first);   
                        for(auto sub : item.second)
                        {
                            DLOG_TRACE("roomid:"<<root->roomid()<<"----- "); 
                            for(auto subb : sub)
                                DLOG_TRACE("roomid:"<<root->roomid()<<", subb: "<< subb);   
                        }
                        break;
                    }
                    DLOG_TRACE("roomid:"<<root->roomid()<<", get time: "<< root->con->getAiThinkTime()); 
                }
  
                __CATCH__
                PERFSTATS_EXIT();
                return 0;
            }
        }
    }
}
