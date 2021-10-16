#include "redis_key.h"

#include <sstream>

namespace RedisKey {

const std::string PREFIX = "eayew_";

std::string Game() {
    return std::string(PREFIX + "game");
}

std::string Account(int game_id) {
    std::stringstream ss;
    ss << PREFIX + "account_" << game_id;
    return std::string(ss.str());
}

std::string Rank(int game_id) {
    std::stringstream ss;
    ss << PREFIX + "rank_" << game_id;
    return std::string(ss.str());
}

std::string Role(int game_id) {
    std::stringstream ss;
    ss << PREFIX + "role_" << game_id;
    return std::string(ss.str());
}

std::string TimerField(int game_id) {
    std::stringstream ss;
    ss << PREFIX + "timer_field_" << game_id;
    return std::string(ss.str());
}

}