import os
os.system("clang++ -Iincludes/ source/main.cpp source/serverC.cpp -lws2_32 -o main")
os.system(".\main")