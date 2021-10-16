
#include "connection.h"

#include "log/glog.h"

#include "servlet.h"

void Connection::run(std::shared_ptr<ServletDispatchRange> servlet) {
    m_servlet = servlet;

    //go std::bind(&Connection::read, shared_from_self());
    //go std::bind(&Connection::write, shared_from_self());
}

void Connection::read() {
    LOG(INFO) << "Connection read";
    for (;;) {
        char data[4096];
        boost::system::error_code ec;
        size_t len = m_socket.read_some(boost::asio::buffer(data), ec);
        if (ec == boost::asio::error::eof) {
            LOG(ERROR) << "error0: " << ec;
            break;
        } else if (ec) {
            LOG(ERROR) << "error1: " << ec;
            break;
        }

        LOG(WARNING) << "len: " << len << "\tdata: " << data;
        //m_servlet->doRequest(shared_from_self(), 1001, std::string(data, len));
    }
}

void Connection::write() {
    LOG(INFO) << "Connection write";
    for (;;) {
        std::string str("hello world!");

        LOG(INFO) << "Connection write begin";
        boost::asio::write(m_socket, boost::asio::buffer(str));
        LOG(INFO) << "Connection write end";

        sleep(10);
    }
}