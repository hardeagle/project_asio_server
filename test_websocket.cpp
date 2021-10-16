#include <memory>

#include <boost/asio.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/websocket/ssl.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/exception/all.hpp>

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include <libgo/libgo.h>

#include "log/glog.h"
#include "net/buffer.h"
#include "net/ssl_certificate.h"

#include "logic/protocol/protocol_account.pb.h"
#include "logic/database/database.pb.h"
#include "logic/util.h"

// class Client {
// public:
//     typedef std::shared_ptr<Client> ptr;

    void init(boost::asio::ssl::context& ctx) {
        try {
            boost::asio::io_context ioc;
            boost::asio::ip::tcp::resolver resolver{ioc};
            boost::beast::websocket::stream<boost::asio::ip::tcp::socket> ws{ioc};

            //std::string host("www.eayew.com");
            std::string host("118.25.56.130");
            std::string port = "9117";
            auto const results = resolver.resolve(host, port);

            auto ep = boost::asio::connect(ws.next_layer(), results);

            host += ':' + std::to_string(ep.port());

            ws.set_option(boost::beast::websocket::stream_base::decorator(
                [](boost::beast::websocket::request_type& req)
                {
                    req.set(boost::beast::http::field::user_agent,
                        std::string(BOOST_BEAST_VERSION_STRING) +
                            " websocket-client-coro");
                }));

            ws.handshake(host, "/");

            for (;;) {
                LOG(INFO) << "--------begin";

                Protocol::C2S_AccountLogin reqMsg;
                reqMsg.set_openid("123");

                std::string msg;
                reqMsg.SerializeToString(&msg);

                uint16_t id = 101;
                uint16_t cap = Buffer::HEADER_SIZE + msg.size();
                int checksum = 0;
                Buffer buffer(cap);
                buffer.push(cap);
                buffer.push(id);
                buffer.push(checksum);
                buffer.write(msg.data(), msg.size());

                LOG(INFO) << "buffer size: " << buffer.size();

                //ws.write(boost::asio::buffer(std::string("1234567890-")));

                // std::vector<uint8_t> vec;
                // vec.push_back(30);
                // vec.push_back(0);
                // vec.push_back(233);
                // vec.push_back(3);
                // vec.push_back(217);
                // vec.push_back(3);
                // vec.push_back(2);
                // vec.push_back(1);
                // for (int i = 0; i < 22; ++i) {
                //     vec.push_back(i + 65);
                // }

                ws.binary(true);

                boost::system::error_code ec;
                ws.write(boost::asio::buffer(buffer.basePos(), buffer.size()), ec);
                //ws.write(boost::asio::buffer(vec));
                LOG(INFO) << "write ec: " << ec;

                boost::beast::flat_buffer rbuffer;
                ws.read(rbuffer);

                co_sleep(1000);

                LOG(INFO) << "---------------end";
            }
        } catch(...) {
            LOG(ERROR) << "throw catch " << boost::current_exception_diagnostic_information();
        }
     }

// private:

// };


int main(int argc, char* argv[]) {
    GLog glog(argv[0]);

    boost::asio::ssl::context ctx{boost::asio::ssl::context::tlsv12_client};
    load_root_certificates(ctx);

    co_timer timer(std::chrono::milliseconds(1), &co_sched);

    int step = 1;
    for (int i = 0; i < 2000; ++i) {
        timer.ExpireAt(std::chrono::milliseconds(i * step), [&] {
            go [&] {
                init(ctx);
            };
        });
    }

    co_sched.Start(4, 8);


    return 0;
}