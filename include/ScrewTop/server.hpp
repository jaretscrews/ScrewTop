#pragma once

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>

namespace ScrewTop {
    class Server {
    public:
        int init();
        void handleConnection();
        void tearDown();
    private:
        int m_sockFd;
        sockaddr_in m_sockAddrIn;
    };
}
