#ifndef __LOGIC_MARQUEE_MANAGER_H__
#define __LOGIC_MARQUEE_MANAGER_H__

#include <memory>
#include <string>

class MarqueeManager {
public:
    typedef std::shared_ptr<MarqueeManager> ptr;

    enum {
        MT_PASS_LEVEL = 1,
        MT_RANK = 2,
        MT_DAILY_PASS_NUM = 3,
    };

    void notifyMarquee(int game_id, int type, const std::string& name, int score, int rank = 1);

private:

};

#endif