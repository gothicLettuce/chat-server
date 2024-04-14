#include <iostream>
#include "serverHeader.h"

int main(){
    std::cout << "Something in the way" << std::endl;
    server new_server("127.0.0.1", 8000);
    new_server.run();
}