#include "util.h"

#include <ifaddrs.h>
#include <iconv.h>
#include <iterator>
#include <list>
#include <netinet/in.h>
#include <time.h>

#include <openssl/aes.h>

#include <google/protobuf/text_format.h>



static const int MAX_RAND = 0x7fff;

void removeString(std::string& str, char c) {
    for (std::string::iterator it = str.begin(); it != str.end();) {
        if (*it == c) {
            str.erase(it++);
            continue;
        }
        ++it;
    }
}

int strlenUtf8(const char* s, size_t s_bytelen) {
    int u8_len = 0;
    for (size_t i = 0; i < s_bytelen; ++i) {
        unsigned char c = s[i];
        if (c >= 0x80) {
            if (c < 0xc0 || c >= 0xf8) {/* not UTF-8 */
                u8_len = -1;
                break;
            } else if (c < 0xe0) {
                ++i;
            } else if (c < 0xf0) {
                i += 2;
            } else {
                i += 3;
            }
        }
        ++u8_len;
    }
    return u8_len;
}

int strlenUtf8(const std::string& s) {
    return strlenUtf8(s.data(), s.size());
}

int strWidthUtf8(const char* s, size_t s_bytelen) {
    int u8_width = 0;
    for (size_t i = 0; i < s_bytelen; ++i) {
        unsigned char c = s[i];
        if (c >= 0x80) {
            if (c < 0xc0 || c >= 0xf8) {
                u8_width = -1;
                break;
            } else if (c < 0xe0) {
                ++i;
            } else if (c < 0xf0) {
                if (i + 2 < s_bytelen) {
                    if (isChinese(&(s[i]))) {
                        ++u8_width;
                    }
                }
                i += 2;
            } else {
                i += 3;
            }
        }
        ++u8_width;
    }
    return u8_width;
}

int strWidthUtf8(const std::string& str) {
    return strWidthUtf8(str.data(), str.size());
}

bool isChinese(const char* s) {
    unsigned char unicode[2] = {0};
    if ((s[0] & 0xf0) != 0xe0 || (s[1] & 0xc0) != 0x80 || (s[2] & 0xc0) != 0x80) {
        return false;
    }
    unicode[0] = ((s[0] & 0x0f) << 4) | ((s[1] & 0x3c) >> 2);
    unicode[1] = ((s[1] & 0x03) << 6) | (s[2] & 0x3f);
    if(unicode[0] >= 0x4e && unicode[0] <= 0x9f) {
        return unicode[0] != 0x9f || unicode[1] <= 0xa5;
    } else {
        return false;
    }
    return false;
}

int hashString(const std::string &str) {
    int ret = 0;
    for (size_t i = 0; i < str.size(); ++i) {
        unsigned char ch = str[i];
        ret = ret * 131 + ch;
    }
    return ret;
}

int stringToInt(const std::string& str) {
    std::stringstream ss;
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            ss << str[i];
        }
    }
    int num = 0;
    ss >> num;
    return num;
}

void splitMulti(std::vector<std::string>& result, const std::string &str, const char *delims) {
    if (str.empty()) {
        return;
    }
    size_t last = 0;
    size_t len = strlen(delims);
    size_t pos = str.find_first_of(delims);
    while (pos != std::string::npos) {
        result.push_back(str.substr(last, pos - last));

        last = pos + len;
        pos = str.find_first_of(delims, last);
    }
    result.push_back(str.substr(last));
}

int randInt(int from, int to) {
    if (from == to) {
        return from;
    }
    double ret = rand() % MAX_RAND;
    return from + ret / MAX_RAND * (to - from);
    //return from + rand() % (to - from);
}

int normalRandInt(int from, int to) {
    int delta = to - from + 1;
    int half = delta >> 1;
    int ret = from;
    ret += randInt(0, half);
    ret += randInt(0, delta - half);
    return ret;
}

double randDouble(double start, double end) {
    double ret = rand() % MAX_RAND;
    return start + (end - start) * (ret / MAX_RAND);
}

void randWithRate(const std::map<int, int> &rates, int num, bool is_repeat, std::list<int> &out) {
    if (rates.empty()) {
        return;
    }
    int total_rate = 0;
    std::map<int, int> rate_map;
    for (std::map<int, int>::const_iterator it = rates.begin(); it != rates.end(); ++it) {
        total_rate += it->second;
        rate_map[total_rate] = it->first;
    }
    if (is_repeat) {
        for (int i = 0; i < num; i++) {
            int rate = randInt(0, rate_map.rbegin()->first);
            out.push_back(rate_map.upper_bound(rate)->second);
        }
        return;
    }
    if (rates.size() <= (size_t)num) {
        for (std::map<int, int>::const_iterator it = rates.begin(); it != rates.end(); ++it) {
            out.push_back(it->first);
        }
        return;
    }
    int max_num = num;
    std::set<int> ids;
    while (num-- > 0) {
        int rate = randInt(0, rate_map.rbegin()->first);
        std::map<int, int>::iterator it = rate_map.upper_bound(rate);
        if (ids.find(it->second) != ids.end()) {
            continue;
        }
        --max_num;
        out.push_back(it->second);
        ids.insert(it->second);
        total_rate -= it->first;
    }
    while (max_num-- > 0) {
        int rate = randInt(0, total_rate);
        for (std::map<int, int>::iterator it = rate_map.begin();
             it != rate_map.end(); ++it) {
            if (ids.find(it->second) != ids.end()) {
                continue;
            }
            if (it->first <= rate) {
                rate -= it->first;
                continue;
            }
            ids.insert(it->second);
            total_rate -= it->first;
            out.push_back(it->second);
            break;
        }
    }
}

int getCurrentSecond() {
    //return time(0);
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

int dayOfWeek(time_t t) {
    return toPosixTime(t).date().day_of_week().as_number();
}

static const boost::posix_time::ptime EPOCH_TIME(boost::gregorian::date(1970, 1, 1));
static const boost::posix_time::ptime TIME_2000(boost::gregorian::date(2000, 1, 1));
static const boost::posix_time::ptime TIME_2020(boost::gregorian::date(2020, 1, 1));

int getLocalSecond() {
    boost::posix_time::time_duration duration =
        boost::posix_time::microsec_clock::local_time() - EPOCH_TIME;
    return duration.total_seconds();
}

int getLocalDayTimeBeg() {
    boost::posix_time::time_duration duration =
        boost::posix_time::microsec_clock::local_time() - EPOCH_TIME;

    int today_sec = duration.hours() * 3600;
    today_sec += duration.minutes() * 60;
    today_sec += duration.seconds();

    return duration.total_seconds() - today_sec;
}

int getCurrentSecond2000() {
    boost::posix_time::time_duration duration =
        boost::posix_time::microsec_clock::local_time() - TIME_2000;
    return duration.total_seconds();
}

int getCurrentSecond2020() {
    boost::posix_time::time_duration duration =
        boost::posix_time::microsec_clock::local_time() - TIME_2020;
    return duration.total_seconds();
}

int getTimeZoneDiff() {
    boost::posix_time::time_duration duration =
        boost::posix_time::second_clock::local_time() - boost::posix_time::second_clock::universal_time();
    return duration.total_seconds();
}

long long getMicroSecond() {
    boost::posix_time::time_duration duration =
        boost::posix_time::microsec_clock::local_time() - EPOCH_TIME;
    return duration.total_microseconds();
}

int getZeroSecond(int curSec, int deltaDay, int hour, int min, int sec) {
    time_t t = time(0);
    if (curSec) {
        t = curSec;
    }
    struct tm cur_tm;
    localtime_r(&t, &cur_tm);
    cur_tm.tm_hour = hour;
    cur_tm.tm_min = min;
    cur_tm.tm_sec = sec;
    return mktime(&cur_tm) + deltaDay * 3600 * 24;
}

int getCurrentDate() {
    const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    static boost::posix_time::time_facet timefmt(
        "%Y%m%d",
        boost::posix_time::time_facet::period_formatter_type(),
        boost::posix_time::time_facet::special_values_formatter_type(),
        boost::posix_time::time_facet::date_gen_formatter_type(),
        1);
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), &timefmt));
    ss << now;
    return atoi(ss.str().c_str());
}

std::string getCurrentDateTime() {
    const boost::posix_time::ptime now = boost::posix_time::microsec_clock::local_time();
    return dateTimeToISOString(now);
}

std::string epochToDateTime(int t) {
    time_t x = t;
    if (t <= 0) {
         x = time(0);
    }
    const boost::posix_time::ptime now = toPosixTime(x);
    return dateTimeToISOString(now);
}

time_t toTimeT(boost::posix_time::ptime t) {
    boost::posix_time::time_duration duration = t - EPOCH_TIME;
    return duration.total_seconds();
}

boost::posix_time::ptime toPosixTime(time_t t) {
    return EPOCH_TIME + boost::posix_time::seconds(t);
}

std::string dateTimeToISOString(const boost::posix_time::ptime &t) {
    static boost::posix_time::time_facet timefmt(
        "%Y-%m-%d %H:%M:%S",
        boost::posix_time::time_facet::period_formatter_type(),
        boost::posix_time::time_facet::special_values_formatter_type(),
        boost::posix_time::time_facet::date_gen_formatter_type(),
        1);
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(), &timefmt));
    ss << t;
    return ss.str();
}

std::string dateToString(const boost::posix_time::ptime &t) {
    static boost::posix_time::time_facet timefmt(
        "%Y-%m-%d",
        boost::posix_time::time_facet::period_formatter_type(),
        boost::posix_time::time_facet::special_values_formatter_type(),
        boost::posix_time::time_facet::date_gen_formatter_type(),
        1);
    std::stringstream ss;
    ss.imbue(std::locale(ss.getloc(),& timefmt));
    ss << t;
    return ss.str();
}

bool isToday(int ts) {
    auto now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto zero = now - now % (24 * 60 * 60) - (8 * 60 * 60);
    return ts >= zero ? true : false;
}
