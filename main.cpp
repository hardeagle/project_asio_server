
#include "log/glog.h"

#include "logic/socket_server.h"

int main(int argc, char *argv[]) {
    GLog glog(argv[0]);

    SocketServer server;
    server.run();

    return 0;
}