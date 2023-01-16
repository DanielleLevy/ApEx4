cmake_minimum_required(VERSION 2.8.12.2)
add_compile_options(-std=c++11)
set(CMAKE_CXX_STANDARD 14)


add_executable(CLI
        Distance.cpp
        Sample.cpp
        InputAndValidation.cpp
        Knn.cpp
        Server.cpp
        DefaultIO.cpp
        CLI.cpp
        Command.cpp)