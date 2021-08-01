#include "ScrewTop/server.hpp"

#include <cstdlib>
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

namespace ScrewTop
{
    int Server::init()
    {
        m_sockFd = socket(AF_INET, SOCK_STREAM, 0);
        if (m_sockFd == -1)
        {
            std::cerr << "Failed to create socket: " << errno << std::endl;
            exit (EXIT_FAILURE);
        }

        m_sockAddrIn.sin_family = AF_INET;
        m_sockAddrIn.sin_addr.s_addr = INADDR_ANY;
        m_sockAddrIn.sin_port = htons(9999);

        if (bind(m_sockFd, (struct sockaddr*)&m_sockAddrIn, sizeof(m_sockAddrIn)) < 0)
        {
            std::cerr << "Failed to bind to port 9999: " << errno << std::endl;
            exit (EXIT_FAILURE);
        }

        return 0;
    }

    void Server::loop()
    {
        if (listen(m_sockFd, 10) < 0)
        {
            std::cerr << "Failed to listen on socket: " << errno << std::endl;
            exit (EXIT_FAILURE);
        }

        auto addrlen = sizeof(m_sockAddrIn);
        auto connection = accept(m_sockFd, (struct sockaddr*)&m_sockAddrIn, (socklen_t*)&addrlen);
        if (connection < 0)
        {
            std::cerr << "Failed to grab connection: " << errno << std::endl;
            exit (EXIT_FAILURE);
        }

        char buffer[100];
        auto bytesRead = read(connection, buffer, 100);
        std::cout << "The message was: " << buffer;

        std::string response = 
        "HTTP/1.1 200 OK\n"
        "Date: Thu, 19 Feb 2009 12:27:04 GMT\n"
        "Server: Apache/2.2.3\n"
        "Last-Modified: Wed, 18 Jun 2003 16:05:58 GMT\n"
        "ETag: \"56d-9989200-1132c580\"\n"
        "Content-Type: text/html\n"
        "Content-Length: 15\n"
        "Accept-Ranges: bytes\n"
        "Connection: close\n"
        "\n"
        "sdfkjsdnbfkjbsf";
        send(connection, response.c_str(), response.size(), 0);

        close(connection);
    }

    void Server::tearDown()
    {
        close(m_sockFd);
    }
}
