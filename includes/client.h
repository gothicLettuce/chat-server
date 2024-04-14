#pragma once 

#include <minwindef.h>
#include <string>
#include <winsock2.h>
#include <psdk_inc/_socket_types.h>

class client{
    SOCKET clientID;

    std::string ip_address;
    int port;
    
    void receiveData();

    public:
    std::string clientName;
    void run();
    client(const char* ip_address, int port);
    ~client();
    void connect_client(const char* ip_address, int port);
};