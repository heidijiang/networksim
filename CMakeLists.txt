cmake_minimum_required(VERSION 3.3)
project(networksim CXX)
include(.eecs211/CMakeLists.txt)

add_program(networksim
            main.cpp
            interface.cpp
            system.cpp
            errors.cpp
            parsing.cpp
            datagram.cpp)

add_test_program(networksim_test
                 networksim_test.cpp
                 system.cpp
                 parsing.cpp
                 datagram.cpp)
