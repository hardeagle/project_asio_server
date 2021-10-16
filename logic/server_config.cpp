#include "logic/server_config.h"

#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

void ServerConfig::init() {
    boost::property_tree::ptree root;
    boost::property_tree::read_json("./json/server.json", root);
    m_avatarNum = root.get<int>("avatar_num");
    m_rankLimit = root.get<int>("rank_limit");
    m_sendTimeout = root.get<int>("send_timeout");
}