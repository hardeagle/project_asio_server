#ifndef __LOGIC_SERVER_CONFIG_H__
#define __LOGIC_SERVER_CONFIG_H__

#include <memory>

class ServerConfig {
public:
    typedef std::shared_ptr<ServerConfig> ptr;

    void init();

    int avatarNum() const { return m_avatarNum; }

    int rankLimit() const { return m_rankLimit; }

    int sendTimeout() const { return m_sendTimeout; }

private:
    int m_avatarNum;
    int m_rankLimit;
    int m_sendTimeout;
};

#endif
