#include "https_request.h"

#include <boost/exception/all.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>

#include "log/glog.h"

#include "ssl_certificate.h"

bool HttpsRequest::request(const std::string& host, const std::string& path, const std::map<std::string, std::string>& params) {
    try {
        boost::asio::io_context ioc;

        ssl::context ctx(ssl::context::tlsv12_client);
        load_root_certificates(ctx);
        ctx.set_verify_mode(ssl::verify_peer);

        boost::asio::ip::tcp::resolver resolver(ioc);
        boost::beast::ssl_stream<boost::beast::tcp_stream> stream(ioc, ctx);

        if(! SSL_set_tlsext_host_name(stream.native_handle(), host.data())) {
            boost::beast::error_code ec{static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category()};
            //throw beast::system_error{ec};
            LOG(ERROR) << "ec: " << ec;
            return false;
        }

        std::string port("443");
        auto const results = resolver.resolve(host, port);
        boost::beast::get_lowest_layer(stream).connect(results);
        stream.handshake(ssl::stream_base::client);

        std::stringstream ss;
        ss << path << "?";
        for (auto it = params.begin(); it != params.end(); ++it) {
            ss << it->first << "=" << it->second << "&";
        }
        std::string target = ss.str();
        if (!target.empty()) {
            target.resize(target.size() - 1);
        }
        int version = 11;

        boost::beast::http::request<boost::beast::http::string_body> req{boost::beast::http::verb::get, target, version};
        req.set(boost::beast::http::field::host, host);
        req.set(boost::beast::http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        boost::beast::http::write(stream, req);

        boost::beast::flat_buffer buffer;
        boost::beast::http::response<boost::beast::http::string_body> res;
        boost::beast::http::read(stream, buffer, res);


        boost::beast::error_code ec;
        stream.shutdown(ec);
        if (ec != boost::asio::error::eof && ec) {
            LOG(ERROR) << "shutdown ec: " << ec;
            //return false;
        }

        if (res.reason() != "OK") {
            LOG(ERROR) << "reason: " << res.reason();
            return false;
        }

        std::stringstream sstream(res.body());
        boost::property_tree::json_parser::read_json(sstream, m_root);
    } catch (...) {
        LOG(ERROR) << boost::current_exception_diagnostic_information();
        return false;
    }

    return true;
}
