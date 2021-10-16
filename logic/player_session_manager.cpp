#include "player_session_manager.h"

#include <mutex>

#include "logic/role.h"
#include "logic/id_generator.h"
#include "logic/player_session.h"
#include "logic/server_resource.h"
#include "redis/redis.h"

PlayerSession::ptr PlayerSessionManager::getPlayer(int game_id, long long role_id) {
    m_mutex.lock();
    auto it = m_onlinePlayers.find(role_id);
    if (it != m_onlinePlayers.end()) {
        return it->second;
    }
    m_mutex.unlock();

    return loadPlayerFromCache(game_id, role_id);
}

void PlayerSessionManager::listOnlinePlayers(std::list<PlayerSession::ptr>& pss) {
    std::lock_guard<std::mutex> lock(m_mutex);
    for (auto it = m_onlinePlayers.begin(); it != m_onlinePlayers.end(); ++it) {
        pss.push_back(it->second);
    }
}

void PlayerSessionManager::listOnlinePlayers(int game_id, std::list<PlayerSession::ptr>& pss) {
    std::lock_guard<std::mutex> lock(m_mutex);
    auto it = m_goPlayers.find(game_id);
    if (it == m_goPlayers.end()) {
        return;
    }
    for (auto it1 = it->second.begin(); it1 != it->second.end(); ++it1) {
        pss.push_back(it1->second);
    }
}

void PlayerSessionManager::playerOnline(PlayerSession::ptr ps) {
    auto role = ps->role();
    if (!role) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    m_onlinePlayers[role->roleId()] = ps;
    m_goPlayers[role->gameId()][role->roleId()] = ps;
}

void PlayerSessionManager::playerOffline(PlayerSession::ptr ps) {
    auto role = ps->role();
    if (!role) {
        return;
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    m_onlinePlayers.erase(role->roleId());
    auto it = m_goPlayers.find(role->gameId());
    if (it != m_goPlayers.end()) {
        it->second.erase(role->roleId());
    }
}

PlayerSession::ptr PlayerSessionManager::loadPlayerFromCache(int game_id, long long role_id) {
    PlayerSession::ptr ps = std::make_shared<PlayerSession>();
    auto role = Role::loadFromCache(game_id, role_id);
    ps->m_role = role;
    return ps;
}

void PlayerSessionManager::handleDisConnect(std::shared_ptr<Session> session) {
    auto ps = std::dynamic_pointer_cast<PlayerSession>(session);
    if (!ps) {
        return;
    }

    playerOffline(ps);
}

void PlayerSessionManager::broadcast(int game_id, uint16_t id, google::protobuf::Message& msg) {
    std::list<PlayerSession::ptr> pss;
    listOnlinePlayers(game_id, pss);

    for (auto it = pss.begin(); it != pss.end(); ++it) {
        (*it)->send(id, msg);
    }
}
