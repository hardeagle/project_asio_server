#ifndef __LOGIC_ID_GENERATOR_H__
#define __LOGIC_ID_GENERATOR_H__

#include <string>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>

class IdGenerator {
public:
    static long long roleId();

private:
    static long long nextId(const std::string& field);

private:
    static const long long m_zoneId = 27;
};

#endif