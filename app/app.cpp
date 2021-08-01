#include "ScrewTop/server.hpp"
#include <iostream>

namespace {
    volatile sig_atomic_t g_SignalStatus = 0;
}

void signal_handler(int signal) {
    g_SignalStatus = signal;
}

int main() {
    signal(SIGINT, signal_handler);

    ScrewTop::Server server;
    server.init();
    while (!g_SignalStatus) {
        server.handleConnection();
    }
    server.tearDown();
    return 0;
}

