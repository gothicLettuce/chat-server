import os
os.system("clang++ -Iincludes/ source/client.cpp -lws2_32 -o client")
os.system(".\client")