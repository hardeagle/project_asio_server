#ifndef __REDIS_REDIS_H__
#define __REDIS_REDIS_H__

#include <chrono>
#include <list>
#include <map>
#include <memory>
#include <mutex>
#include <set>

#include <boost/exception/all.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

#include <boost/asio.hpp>
#include <boost/asio/awaitable.hpp>
#include <boost/asio/detached.hpp>
#include <boost/asio/co_spawn.hpp>
#include <hiredis/hiredis.h>

#include "log/glog.h"

class RedisConfig {
friend class RedisConnection;
friend class RedisConnectionPool;
public:
    typedef std::shared_ptr<RedisConfig> ptr;

    RedisConfig(const std::string &path) {
        boost::property_tree::ptree root;
        boost::property_tree::read_json(path, root);
        m_host = root.get<std::string>("host");
        m_port = root.get<int>("port");
        m_timeoutSecond = root.get<int>("timeout_second");
        m_timeoutMicroSecond = root.get<int>("timeout_micro_second");
        m_maxConnection = root.get<size_t>("max_connection");
        m_maxIdleConnection = root.get<size_t>("max_idle_connection");
        LOG(INFO) << "RedisConfig ";
        LOG(INFO) << "m_host: " << m_host;
        LOG(INFO) << "m_port: " << m_port;
        LOG(INFO) << "m_timeoutSecond: " << m_timeoutSecond;
        LOG(INFO) << "m_timeoutMicroSecond: " << m_timeoutMicroSecond;
        LOG(INFO) << "m_maxConnection: " << m_maxConnection;
        LOG(INFO) << "m_maxConnection: " << m_maxIdleConnection;
    }

private:
    std::string m_host;
    int m_port;
    int m_timeoutSecond;
    int m_timeoutMicroSecond;
    size_t m_maxConnection;
    size_t m_maxIdleConnection;
};

class RedisResult {
public:
    //typedef std::shared_ptr<RedisResult> ptr;

    RedisResult()
        : m_reply(nullptr) {
    }

    RedisResult(redisReply *reply)
        : m_reply(reply) {
    }

    ~RedisResult() {
        if (m_reply) {
            freeReplyObject(m_reply);
        }
    }

    template<typename T>
    bool get(T& val) {
        try {
            if (!m_reply) {
                LOG(ERROR) << "m_reply is null!";
                return false;
            }
            if (m_reply->type == REDIS_REPLY_ERROR) {
                LOG(ERROR) << "redis reply error:" << std::string(m_reply->str, m_reply->len);
                return false;
            }
            if (m_reply->type == REDIS_REPLY_NIL) {
                return true;
            }
            if (m_reply->type == REDIS_REPLY_INTEGER) {
                val = boost::lexical_cast<T>(m_reply->integer);
                return true;
            }
            if (m_reply->type == REDIS_REPLY_STRING) {
                val = boost::lexical_cast<T>(std::string(m_reply->str, m_reply->len));
                return true;
            }
            if (m_reply->type == REDIS_REPLY_ARRAY && m_reply->elements != 0) {
                val = boost::lexical_cast<T>(std::string(m_reply->element[0]->str, m_reply->element[0]->len));
            }
        } catch(...) {
            LOG(FATAL) << boost::current_exception_diagnostic_information();
        }
        return true;
    }

    template<typename T>
    bool get(std::list<T>& vals) {
        try {
            if (!m_reply) {
                LOG(ERROR) << "m_reply is null!";
                return false;
            }
            if (m_reply->type == REDIS_REPLY_ERROR) {
                LOG(ERROR) << "redis reply error:" << std::string(m_reply->str, m_reply->len);
                return false;
            }
            if (m_reply->type == REDIS_REPLY_NIL) {
                return true;
            }
            if (m_reply->type == REDIS_REPLY_INTEGER) {
                vals.emplace_back(boost::lexical_cast<T>(m_reply->integer));
                return true;
            }
            if (m_reply->type == REDIS_REPLY_STRING) {
                vals.emplace_back(boost::lexical_cast<T>(std::string(m_reply->str, m_reply->len)));
                return true;
            }
            if (m_reply->type == REDIS_REPLY_ARRAY) {
                for (size_t i = 0; i < m_reply->elements; ++i) {
                    vals.emplace_back(boost::lexical_cast<T>(std::string(
                        m_reply->element[i]->str, m_reply->element[i]->len
                    )));
                }
            }
        } catch(...) {
            LOG(FATAL) << boost::current_exception_diagnostic_information();
        }
        return true;
    }

    template<typename T>
    bool get(std::set<T>& vals) {
        try {
            if (!m_reply) {
                LOG(ERROR) << "m_reply is null!";
                return false;
            }
            if (m_reply->type == REDIS_REPLY_ERROR) {
                LOG(ERROR) << "redis reply error:" << std::string(m_reply->str, m_reply->len);
                return false;
            }
            if (m_reply->type == REDIS_REPLY_NIL) {
                return true;
            }
            if (m_reply->type == REDIS_REPLY_INTEGER) {
                vals.insert(boost::lexical_cast<T>(m_reply->integer));
                return true;
            }
            if (m_reply->type == REDIS_REPLY_STRING) {
                vals.insert(boost::lexical_cast<T>(std::string(m_reply->str, m_reply->len)));
                return true;
            }
            if (m_reply->type == REDIS_REPLY_ARRAY) {
                for (size_t i = 0; i < m_reply->elements; ++i) {
                    vals.insert(boost::lexical_cast<T>(std::string(
                        m_reply->element[i]->str, m_reply->element[i]->len
                    )));
                }
            }
        } catch(...) {
            LOG(FATAL) << boost::current_exception_diagnostic_information();
        }
        return true;
    }

    template<typename K, typename V>
    bool get(std::map<K, V>& vals) {
        try {
            if (!m_reply) {
                LOG(ERROR) << "m_reply is null!";
                return false;
            }
            if (m_reply->type == REDIS_REPLY_ERROR) {
                LOG(ERROR) << "redis reply error:" << std::string(m_reply->str, m_reply->len);
                return false;
            }
            if (m_reply->type == REDIS_REPLY_NIL) {
                return true;
            }
            if (m_reply->type != REDIS_REPLY_ARRAY) {
                return true;
            }
            if ((m_reply->elements & 0x1) != 0) {
                return true;
            }
            for (size_t i = 0; i < m_reply->elements; i += 2) {
                K key = boost::lexical_cast<K>(std::string(m_reply->element[i]->str, m_reply->element[i]->len));
                V val = boost::lexical_cast<V>(std::string(m_reply->element[i + 1]->str, m_reply->element[i + 1]->len));
                vals[key] = val;
            }
        } catch(...) {
            LOG(FATAL) << boost::current_exception_diagnostic_information();
        }
        return true;
    }


private:
    redisReply *m_reply;
};

class RedisConnection {
public:
    typedef std::shared_ptr<RedisConnection> ptr;

    RedisConnection(const RedisConfig::ptr config)
        : m_config(config) {
        struct timeval timeout = { config->m_timeoutSecond, config->m_timeoutMicroSecond };
        m_ctx = redisConnectWithTimeout(config->m_host.data(), config->m_port, timeout);
        if (m_ctx == NULL || m_ctx->err) {
            if (m_ctx) {
                LOG(ERROR) << "RedisConnection error: " << m_ctx->err;
                redisFree(m_ctx);
            } else {
                LOG(ERROR) << "RedisConnection error, can't allocate redis context";
            }
            return;
        }
    }

    ~RedisConnection() {
        if (m_ctx) {
            redisFree(m_ctx);
        }
    }

    template<typename... Args>
    RedisResult exec(Args... args) {
        if (!m_ctx) {
            return RedisResult();
        }

        std::vector<std::string> cmds;
        exec(cmds, args...);

        return realExec(cmds);
    }

    template<typename T, typename... Args>
    RedisResult exec(const std::set<T>& fields, Args... args) {
        if (!m_ctx) {
            return RedisResult();
        }

        std::vector<std::string> cmds;
        exec(cmds, args...);

        for (auto& val : fields) {
            cmds.push_back(boost::lexical_cast<std::string>(val));
        }

        return realExec(cmds);
    }

    template<typename T>
    RedisResult exec2(const std::string& cmd, const std::string& key, const std::set<T>& fields) {
        if (!m_ctx) {
            return RedisResult();
        }

        std::vector<std::string> cmds;
        cmds.push_back(cmd);
        cmds.push_back(key);

        for (auto& val : fields) {
            cmds.push_back(boost::lexical_cast<std::string>(val));
        }

        return realExec(cmds);
    }

private:
public:
    RedisResult realExec(std::vector<std::string>& cmds) {
        size_t argc = cmds.size();
        std::vector<const char*> argvs(argc);
        std::vector<size_t> argvs_len(argc);
        for (size_t i = 0; i < argc; ++i) {
            argvs[i] = cmds[i].data();
            argvs_len[i] = cmds[i].size();
        }

        redisReply *reply = (redisReply*)redisCommandArgv(m_ctx, argc, &argvs[0], &argvs_len[0]);
        return reply ? RedisResult(reply) : RedisResult();
    }

    template<typename T, typename... Args>
    void exec(std::vector<std::string>& cmds, T& cmd, Args... args) {
        cmds.push_back(boost::lexical_cast<std::string>(cmd));
        exec(cmds, args...);
    }

    void exec(std::vector<std::string>& cmds) {
    }

private:
    RedisConfig::ptr m_config;

    redisContext *m_ctx;
};



class RedisConnectionPool {
public:
    typedef std::shared_ptr<RedisConnectionPool> ptr;

    RedisConnectionPool(boost::asio::io_context& ioc)
        : m_ioc(ioc) {
    }

    void init() {
        m_config.reset(new RedisConfig("./json/redis_config.json"));
        // m_pool.reset(new co::ConnectionPool<RedisConnection>([this] {
        //     return new RedisConnection(m_config);
        // }, NULL, m_config->m_maxConnection, m_config->m_maxIdleConnection));
        // m_pool->Reserve(m_config->m_maxIdleConnection);
        for (int i = 0; i < 1000; ++i) {
            RedisConnection* rc = new RedisConnection(m_config);
            m_rcs.push_back(rc);
        }
    }

    void release(RedisConnection* rc) {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_rcs.push_back(rc);
    }

    RedisConnection::ptr get() {
        RedisConnection* rc = nullptr;

        std::unique_lock<std::mutex> lock(m_mutex);
        m_cv.wait(lock, [this] {
            return !m_rcs.empty();
        });
        rc = m_rcs.front();
        m_rcs.pop_front();
        lock.unlock();

        RedisConnection::ptr prc(rc, std::bind(&RedisConnectionPool::release, this, std::placeholders::_1));
        return prc;
    }

    // set
    template<typename T>
    bool sadd(const std::string& key, const T& member) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("sadd", key, member);
        return true;
    }

    template<typename T>
    bool smembers(std::set<T>& members, const std::string& key) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        return rc->exec("smembers", key).get<T>(members);
    }

    template<typename T>
    bool srem(const std::string& key, const std::set<T>& memebers) {
        if (memebers.empty()) {
            LOG(ERROR) << "memebers is empty";
            return false;
        }
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        //rc->exec(memebers, "srem", key);
        rc->exec2("srem", key, memebers);
        return true;
    }

    bool zadd(const std::string& key, int score, long long member) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("zadd", key, score, member);
        return true;
    }

    int zscore(const std::string& key, long long member) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return 0;
        }
        int score = 0;
        if (rc->exec("zscore", key, member).template get<int>(score)) {
            return score;
        }
        return 0;
    }

    template<typename T>
    bool zrevrank(int& val, const std::string& key, T& member) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        return rc->exec("zrevrank", key, member).template get<int>(val);
    }

    template<typename K, typename V>
    bool zrevrange(std::map<K, V>& vals, const std::string& key, int start, int stop) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("zrevrange", key, start, stop, "withscores").get<K, V>(vals);
        return true;
    }

    // hash
    template<typename T, typename U>
    bool hset(const std::string& key, const T& field, const U& val) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("hset", key, field, val);
        return true;
    }

    template<typename T, typename U>
    bool hget(T& val, const std::string& key, const U& field) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("hget", key, field).template get<T>(val);
        return true;
    }

    template<typename T, typename U>
    bool hmget(std::list<T>& vals, const std::string& key, const std::set<U>& fields) {
        if (fields.empty()) {
            LOG(ERROR) << "fields is empty";
            return false;
        }
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        //return rc->exec(fields, "hmget", key).get(vals);
        rc->exec2("hmget", key, fields).get(vals);
        return true;
    }

    template<typename K, typename V>
    bool hgetall(std::map<K, V>& vals, const std::string& key) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "get connection fail";
            return false;
        }
        rc->exec("hgetall", key).get(vals);
        return true;
    }

    template<typename T>
    bool hdel(const std::string& key, const std::set<T>& fields) {
        if (fields.empty()) {
            LOG(ERROR) << "fields is empty";
            return false;
        }
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "getConnection fail";
            return false;
        }
        //rc->exec(fields, "hdel", key);
        rc->exec2("hdel", key, fields);
        return true;
    }

    template<typename T>
    bool hincrby(T& val, const std::string& key, const std::string& field, int increment = 1) {
        RedisConnection::ptr rc = get();
        if (!rc) {
            LOG(ERROR) << "getConnection fail";
            return false;
        }
        rc->exec("hincrby", key, field, increment).get(val);
        return true;
    }

private:
    boost::asio::io_context& m_ioc;

    RedisConfig::ptr m_config;

    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::list<RedisConnection*> m_rcs;

    //std::shared_ptr<co::ConnectionPool<RedisConnection> > m_pool;
};

#endif