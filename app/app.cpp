#include "ScrewTop/server.hpp"

int main()
{
    ScrewTop::Server server;
    server.init();
    server.loop();
    server.tearDown();
    return 0;
}

