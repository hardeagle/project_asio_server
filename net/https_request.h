#ifndef __NET_HTTPS_REQUEST_H__
#define __NET_HTTPS_REQUEST_H__

#include <map>
#include <string>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

class HttpsRequest {
public:
    bool request(const std::string& host, const std::string& path, const std::map<std::string, std::string>& params);

    boost::property_tree::ptree& rspRoot() { return m_root; }

private:
    boost::property_tree::ptree m_root;
};

#endif