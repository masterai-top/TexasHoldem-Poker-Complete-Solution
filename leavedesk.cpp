#include "Comm/ITableGame.h"
#include "common/macros.h"
#include "common/nndef.h"
#include "gameroot.h"
#include "logic/gamelogic/core/leavedesk.h"
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

            int LeaveDesk(GameRoot *root, bool bTimeOut)
            {
                if(root->pro->getProcess() != nil_nnstate || root->con->isGameBegin())
                {
                    DLOG_TRACE("roomid:" << root->roomid() << ",process err. process : " << root->pro->getProcess());
                    return 0;
                }

                //检查离开状态
                std::vector<long> vdelUser;
                std::map<cid_t, User> &usermap = root->con->refUserMap();
                for (auto it = usermap.begin(); it != usermap.end(); it++)
                {
                    if(it->second.isLeft() || it->second.isTuoGuan())
                    {
                        DLOG_TRACE("roomid:" << root->roomid() << ",user. uid: " << it->second.getUid() << ", cid: "<< it->first<< ", left: "<< it->second.isLeft() << ", tuoguan: "<<it->second.isTuoGuan() );
                        vdelUser.push_back(it->second.getUid());
                        
                        XGameDDZProto::DDZ_msg2cLeaveNotify leave_notify;
                        leave_notify.set_icid(it->first);
                        sendAllClientMessage<XGameDDZProto::DDZ_msg2cLeaveNotify>(XGameDDZProto::DDZ_msg2cLeaveNotify_E, leave_notify, root);
                    }
                }
                RemoveUser(root, vdelUser);

                if(vdelUser.size() > 0 || bTimeOut)
                {
                    std::vector<long> vrematchUser;
                    for (auto it = usermap.begin(); it != usermap.end(); it++)
                    {
                        if(it->second.isReady())
                        {
                            DLOG_TRACE("roomid:" << root->roomid() << ",user left. uid: " << it->second.getUid() << ", cid: "<< it->first << ", ready: "<< it->second.isReady());
                            vrematchUser.push_back(it->second.getUid());

                            XGameDDZProto::DDZ_msg2cLeaveNotify leave_notify;
                            leave_notify.set_icid(it->first);
                            sendAllClientMessage<XGameDDZProto::DDZ_msg2cLeaveNotify>(XGameDDZProto::DDZ_msg2cLeaveNotify_E, leave_notify, root);
                        }
                    }

                    for(auto uid : vrematchUser)
                    {
                        DLOG_TRACE("roomid:" << root->roomid() << ",user rematch. uid: " << uid);
                        XGameDDZProto::DDZ_msg2cReMatchGame rematch_notify;
                        sendClientMessage<XGameDDZProto::DDZ_msg2cReMatchGame>(uid, XGameDDZProto::DDZ_msg2cReMatchGame_E, rematch_notify, root);
                    }

                    RemoveUser(root, vrematchUser); 
                }
                               
                return 0;
            }

            int RemoveUser(GameRoot *root, std::vector<long> vdelUser)
            {
                root->con->clearCalInfo();
                for (auto iter = vdelUser.begin(); iter != vdelUser.end(); iter++)
                {
                    User* user = root->con->getUserByUid(*iter);
                    if(user)
                    {
                        //DLOG_TRACE("roomid:" << root->roomid() << ", del, uid: " << *iter << ", left: " << user->isLeft() << ", ready: "<< user->isReady());
                        root->con->delUser(*iter);

                        //站起消息
                        TGAME_Stand tmm;
                        tmm.lPlayerID = *iter;
                        tmm.iType = user->isSelfLevel() ? 1 : 0;
                        sendRoomMessage<TGAME_Stand>(TGAME_Stand_E, tmm, root);
                    }
                    else
                    {
                        DLOG_TRACE("roomid:" << root->roomid() << ", del user err, uid: " << *iter);
                    }
                }
                return 0;
            }
        }
    }
}
