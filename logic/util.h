#ifndef __LOGIC_UTIL_H__
#define __LOGIC_UTIL_H__

#include <stddef.h>
#include <list>
#include <map>
#include <set>
#include <string>

#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>


void removeString(std::string& str, char c);

int strlenUtf8(const char* s, size_t s_bytelen);
int strlenUtf8(const std::string& s);
int strWidthUtf8(const char* s, size_t s_bytelen);
int strWidthUtf8(const std::string& str);
bool isChinese(const char* s);

int hashString(const std::string &str);
int stringToInt(const std::string& str);

void splitMulti(std::vector<std::string>& result, const std::string& str, const char *delims);

double randDouble(double start = 0, double end = 1);
int randInt(int from = 0, int to = 100);
int normalRandInt(int from, int to);
void randWithRate(const std::map<int, int> &rates, int num, bool is_repeat, std::list<int> &out);

int dayOfWeek(time_t t);
int getCurrentSecond();
int getCurrentSecond2000();
int getCurrentSecond2020();
int getLocalSecond();
int getTimeZoneDiff();
long long getMicroSecond();
int getCurrentDate();
int getZeroSecond(int curSec, int deltaDay = 0, int hour = 0, int min = 0, int sec = 0);
int getLocalDayTimeBeg();

std::string getCurrentDateTime();
std::string epochToDateTime(int t = 0);

time_t toTimeT(boost::posix_time::ptime t);
boost::posix_time::ptime toPosixTime(time_t t);
std::string dateTimeToISOString(const boost::posix_time::ptime &t);
std::string dateToString(const boost::posix_time::ptime &t);

bool isToday(int ts);

#endif