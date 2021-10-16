#include "marquee_manager.h"

#include "logic/protocol/protocol_id.pb.h"
#include "logic/protocol/protocol_rank.pb.h"
#include "logic/player_session_manager.h"
#include "logic/server_resource.h"

void MarqueeManager::notifyMarquee(int game_id, int type, const std::string& name, int score, int rank) {
    Protocol::S2C_RankMarquee msg;
    msg.set_type(type);
    msg.set_name(name);
    msg.set_score(score);
    msg.set_rank(rank);
    ServerResource::get()->psMgr()->broadcast(game_id, Protocol::MsgId::S2C_RANK_MARQUEE, msg);
}