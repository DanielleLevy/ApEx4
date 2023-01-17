cmake_minimum_required(VERSION 2.8.12.2)
add_compile_options(-std=c++11 -pthread)
set(CMAKE_CXX_STANDARD 14)
project(ApEx4)
find_package(Threads REQUIRED)


add_executable(Server
        Distance.cpp
        Sample.cpp
        InputAndValidation.cpp
        Knn.cpp
        Server.cpp
        DefaultIO.cpp
        CLI.cpp
        Command.cpp)
target_link_libraries(Server ${CMAKE_THREAD_LIBS_INIT})
