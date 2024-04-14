
#include <client.h>
#include <minwindef.h>
#include <psdk_inc/_socket_types.h>
#include <psdk_inc/_wsadata.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif



client::client(const char* ip_address, int port){

    std::cout<<"Enter your name: ";
    std::getline(std::cin , clientName);

    //Loading DLL
    WSADATA metaData;
    WORD ver = MAKEWORD(2, 2);
    int err = WSAStartup(ver, &metaData);
    
#ifdef DEBUG
    if(err != 0){
        std::cerr << "[c] Error loading DLL\n";
    } else {
        std::cerr << "[c] DLL loaded\n";
    }
#endif

    //creating the client socket
    clientID = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

#ifdef DEBUG
    if(clientID == INVALID_SOCKET){
        std::cerr << "[c] Error creating the client\n";
    } else {
        std::cerr << "[c] Client successfully created\n";
    }
#endif

    // connecting the client to the server
    sockaddr_in clientdata;
    clientdata.sin_family = AF_INET;
    InetPton(AF_INET, ip_address, &clientdata.sin_addr.S_un);
    clientdata.sin_port = htons(port);

    int isconnect = connect(clientID, (SOCKADDR*)&clientdata, sizeof(clientdata));

#ifdef DEBUG
    if(isconnect == SOCKET_ERROR){
        std::cerr << "[c] Error connecting the client\n";
        WSACleanup();
        closesocket(isconnect);
    } else {
        std::cerr << "[c] Client connected at port: " << port << "\n";
    }
#endif
}

void client::receiveData(){

    char buff[1024];
    while (true) {

        int rs = recv(clientID, buff, 1024, 0);
        if(rs <= 0) break;

        buff[rs] = '\0';
        std::cout<<buff<<"\n";
    }
}


void client::run(){
    // std::thread t1(&client::recieveData, this);
    std::thread receiveChannel(&client::receiveData, this);

    while(true){
        //sending data
        std::string buffer;
        // printf("Enter the message: ");
        std::getline(std::cin,buffer);
        if(buffer == "EXIT") exit(0);

        buffer = clientName + ": " + buffer;

        int byteCount = send(clientID, buffer.c_str(), buffer.length(), 0);

#ifdef DEBUG
        if(byteCount == SOCKET_ERROR){
            std::cout << "Error sending data from client%ld\n" << WSAGetLastError();
            break;
        } 
#endif
    }

    receiveChannel.join();
}


client::~client(){
    WSACleanup();
    closesocket(clientID);
}


int main(){
    client new_client("127.0.0.1", 8000);
    new_client.run();
}


// void client::recieveData() {
//     while(true){
//     char recieveBuffer[200] = "";
//         int byteCount = recv(clientID, recieveBuffer, 200, 0);
//         if(byteCount < 0){
//             printf("[Failure] - Error recieving data client side %ld\n", WSAGetLastError());
//             std::cout << "Error recieving data on client side " << WSAGetLastError() << '\n';
//         } 
//         else {
//             // printf("\nRecieved data by client: %s\n", recieveBuffer);
//             std::cout << '\n' << recieveBuffer;
//         }
//     }
// }