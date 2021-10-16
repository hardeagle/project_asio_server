
#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include "log/glog.h"
#include "redis/redis.h"

#include "logic/database/database.pb.h"
#include "logic/redis_key.h"
#include "logic/server_resource.h"


int main(int argc, char* argv[]) {
    GLog glog(argv[0]);

    LOG(WARNING) << "begin";

    try {
        ServerResource::ptr res = ServerResource::get();
        res->init();

        boost::property_tree::ptree root;
        boost::property_tree::read_json("./json/update_game.json", root);
        auto game_id = root.get<int>("game_id");
        auto platform = root.get<int>("platform");
        auto name = root.get<std::string>("name");
        auto appid = root.get<std::string>("appid");
        auto secret = root.get<std::string>("secret");

        Database::Game game;
        game.set_game_id(game_id);
        game.set_platform(platform);
        game.set_name(name);
        game.set_appid(appid);
        game.set_secret(secret);
        std::string serial;
        game.SerializeToString(&serial);

        res->rcPool()->hset(RedisKey::Game(), game_id, serial);


        // check test
        {
            LOG(WARNING) << "----check begin---";
            std::string strGame;
            res->rcPool()->hget(strGame, RedisKey::Game(), game_id);
            Database::Game game;
            game.ParseFromString(strGame);
            LOG(WARNING) << "game_id: " << game.game_id();
            LOG(WARNING) << "platform: " << game.platform();
            LOG(WARNING) << "name: " << game.name();
            LOG(WARNING) << "appid: " << game.appid();
            LOG(WARNING) << "secret: " << game.secret();
            LOG(WARNING) << "----check end---";
        }

    } catch(...) {
        LOG(ERROR) << boost::current_exception_diagnostic_information();
        return 0;
    }

    LOG(WARNING) << "end";

    return 0;
}