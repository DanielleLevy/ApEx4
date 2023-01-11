cmake_minimum_required(VERSION 2.8.12.2)
add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 14)

add_executable(client.out "Header.h"
        "Distance.cpp"
        "Distance.h"
        "Sample.cpp"
        "Sample.h"
        "InputAndValidation.cpp" Knn.cpp  Client.cpp Client.h)
add_executable(server.out  "Header.h"
        "Distance.cpp"
        "Distance.h"
        "Sample.cpp"
        "Sample.h"
        "InputAndValidation.cpp" Knn.cpp Server.cpp Server.h)