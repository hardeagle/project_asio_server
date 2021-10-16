
#include "ws_connection.h"

#include <boost/endian/conversion.hpp>
#include <boost/exception/all.hpp>

#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>

#include "log/glog.h"

#include "buffer.h"
#include "resource.h"
#include "scheduler.h"
#include "servlet.h"
#include "ssl_certificate.h"

void WsConnection::run() {
    try {
        setupWss();
    } catch(...) {
        LOG(ERROR) << "setup wss fail " << boost::current_exception_diagnostic_information();
    }
}

void WsConnection::send(uint16_t id, google::protobuf::Message& msg) {
    std::string str;
    msg.SerializeToString(&str);
    send(id, str);
}

void WsConnection::send(uint16_t id, const std::string& msg) {
    uint16_t cap = Buffer::HEADER_SIZE + msg.size();
    int checksum = 0;
    Buffer buffer(cap);
    buffer.push(cap);
    buffer.push(id);
    buffer.push(checksum);
    buffer.write(msg.data(), msg.size());

    wss().async_write(boost::asio::buffer(msg.data(), msg.size()), [](const boost::system::error_code& ec, std::size_t bytes_transferred) {
        //LOG(ERROR) << "-------async write ec " << ec;
    });

    //m_wMsgs.push_back(buffer);
}

void WsConnection::setupWss() {
    m_wss.reset(new WebSocketStream(std::move(m_socket)));

    wss().binary(true);
    wss().set_option(boost::beast::websocket::stream_base::timeout::suggested(boost::beast::role_type::server));
    wss().set_option(boost::beast::websocket::stream_base::decorator(
        [](boost::beast::websocket::response_type &res) {
            res.set(boost::beast::http::field::server, std::string(BOOST_BEAST_VERSION_STRING) + "websocket");
    }));

    wss().async_accept([this, self = shared_from_self()](boost::system::error_code ec) {
        doRead();
    });
}

void WsConnection::doRead() {
    m_buffer.consume(m_buffer.size());
    wss().async_read(m_buffer, [this, self = shared_from_self()](boost::beast::error_code ec, std::size_t bytes_transferred) {
        if (ec) {
            close();
            return;
        }

        boost::beast::flat_buffer& buffer = m_buffer;

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

        m_resource->scheduler()->addTask(createTask(std::bind(&ServletDispatchRange::doRequest, m_resource->servlet(),
            shared_from_self(), id, std::string((char*)buffer.data().data(), buffer.size()))));

        doRead();
    });
}

void WsConnection::doWrite() {

}

void WsConnection::close() {
    if (m_func) {
        m_func(shared_from_this());
        m_func = nullptr;
    }

    if (wss().is_open()) {
        //boost::beast::error_code ec;
        wss().close(boost::beast::websocket::close_code::normal);
        //wss().shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        //wss().close();
    }
}