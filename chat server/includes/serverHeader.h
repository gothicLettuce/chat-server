#pragma once

#include <minwindef.h>
#include <string>
#include <thread>
#include <vector>
#include <winsock2.h>
#include <psdk_inc/_socket_types.h>

class server {
    SOCKET serverID;
    std::vector<SOCKET> client_conns;
    std::vector<std::thread> thread_pool;
    void handleClients(SOCKET HClient);
    void sendData(std::vector<std::thread> thread_pool, char sendBuffer[]);

    std::string ip_address;
    int port;

    public:
    server(const char* addr, int port);
    ~server();
    void run();
};
