
#include "wss_connection.h"

#include <boost/endian/conversion.hpp>
#include <boost/exception/all.hpp>

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>


#include "log/glog.h"

#include "buffer.h"
#include "servlet.h"
#include "ssl_certificate.h"

void WssConnection::run(std::shared_ptr<ServletDispatchRange> servlet) {
    m_servlet = servlet;

    try {
        setupWss();
    } catch(...) {
        LOG(ERROR) << "setup wss fail " << boost::current_exception_diagnostic_information();
    }

    //go std::bind(&WssConnection::read, shared_from_self());
    //go std::bind(&WssConnection::write, shared_from_self());
}

void WssConnection::send(uint16_t id, google::protobuf::Message& msg) {
    std::string str;
    msg.SerializeToString(&str);
    send(id, str);
}

void WssConnection::send(uint16_t id, const std::string& msg) {
    uint16_t cap = Buffer::HEADER_SIZE + msg.size();
    int checksum = 0;
    Buffer buffer(cap);
    buffer.push(cap);
    buffer.push(id);
    buffer.push(checksum);
    buffer.write(msg.data(), msg.size());

    //m_wChannel.TryPush(std::move(buffer));
    //m_wChannel << buffer;
}

void WssConnection::setupWss() {
    m_wss.reset(new WebSocketSslStream(std::move(m_socket), m_sslContext));

    wss().next_layer().handshake(boost::asio::ssl::stream_base::server);

    wss().binary(true);
    wss().set_option(boost::beast::websocket::stream_base::timeout::suggested(boost::beast::role_type::server));
    wss().set_option(boost::beast::websocket::stream_base::decorator(
        [](boost::beast::websocket::response_type &res) {
            res.set(boost::beast::http::field::server, std::string(BOOST_BEAST_VERSION_STRING) + "websocket");
    }));
    wss().accept();
}

void WssConnection::read() {
    for (;;) {
        boost::beast::flat_buffer buffer;
        boost::system::error_code ec;
        wss().read(buffer, ec);
        if (ec) {
            close();
            break;
        }

        uint16_t len = 0;
        memcpy(&len, buffer.data().data(), sizeof(len));
        buffer.consume(sizeof(len));
        //len = boost::endian::big_to_native(len);
        LOG(INFO) << "len: " << len << "\tsize: " << buffer.size();

        uint16_t id = 0;
        memcpy(&id, buffer.data().data(), sizeof(id));
        buffer.consume(sizeof(id));
        //id = boost::endian::big_to_native(id);
        LOG(INFO) << "id: " << id << "\tsize: " << buffer.size();

        int checksum = 0;
        memcpy(&checksum, buffer.data().data(), sizeof(checksum));
        buffer.consume(sizeof(checksum));
        //checksum = boost::endian::big_to_native(checksum);
        LOG(INFO) << "checksum: " << checksum << "\tsize: " << buffer.size();

        //m_servlet->doRequest(shared_from_self(), id, std::string((char*)buffer.data().data(), buffer.size()));
    }
}

void WssConnection::write() {
    // while (wss().next_layer().next_layer().is_open()) {
    //     boost::system::error_code ec;
    //     Buffer buffer;
    //     if (!m_wChannel.TimedPop(buffer, std::chrono::seconds(100))) {
    //         close();
    //         break;
    //     }
    //     wss().write(boost::asio::buffer(buffer.basePos(), buffer.size()), ec);
    //     if (ec) {
    //         close();
    //         break;
    //     }
    // }
}

void WssConnection::close() {
    // std::lock_guard<co_mutex> lock(m_mutex);
    // m_wChannel.Close();

    if (m_func) {
        m_func(shared_from_this());
        m_func = nullptr;
    }

    if (wss().next_layer().next_layer().is_open()) {
        boost::beast::error_code ec;
        wss().next_layer().next_layer().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        wss().next_layer().next_layer().close();
    }
}