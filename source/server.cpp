#include <cstddef>
#include <iostream>
#include "serverHeader.h"
#include <winsock2.h>
#include <minwindef.h>
#include <psdk_inc/_ip_types.h>
#include <psdk_inc/_socket_types.h>
#include <psdk_inc/_wsadata.h>
#include <ws2tcpip.h> //inetpton


server::server(const char* addr, int port){
    //Loading DLL
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA window_data;
    int dll_init = WSAStartup(wVersionRequested, &window_data);
    if(dll_init != 0){
        std::cout << "Failed to load dll\n";
    } else {
        std::cout << "Loaded dll\n";
    }

    //Creating a socket
    serverID = INVALID_SOCKET;
    serverID = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(serverID == INVALID_SOCKET){
        std::cout << "Failed creating server socket\n";
        WSACleanup();
    } else {
        std::cout<<"server socket created\n";
    }
    closesocket(serverID);

    //Binding server 
    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, "127.0.0.1", &service.sin_addr.S_un);
    service.sin_port = htons(port);
    if(bind(serverID, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
        std::cout<<"Failed binding the server\n";
        closesocket(serverID);
        WSACleanup();
    } else {
        std::cout << "server socket has been binded\n";
    }

    //Listening for connections
    if(listen(serverID, 1) == SOCKET_ERROR){
        std::cout << "Failed listening for a client\n";
    } else {
        std::cout << "Listening at port: " << port << "\n";
    }
}

void server::run(){
    while(true){
        int client_fd = accept(serverID, NULL, NULL);
        if(client_fd == INVALID_SOCKET){
            std::cout << "Failed accepting a client\n";
        } else {
            std::cout << "connected to a client\n";
        }
        client_conns.emplace_back(client_fd);
    }
}