#ifndef __LOGIC_REDIS_KEY_H__
#define __LOGIC_REDIS_KEY_H__

#include <string>

namespace RedisKey {

std::string Game();

std::string Account(int game_id);

std::string Rank(int game_id);

std::string Role(int game_id);

std::string TimerField(int game_id);

}

#endif