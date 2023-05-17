cmake_minimum_required(VERSION 3.24)
project(struktury_danych)

set(CMAKE_CXX_STANDARD 14)

add_executable(struktury_danych
        main.cpp src/AVLtree.cpp include/AVLtree.h src/SkipList.cpp include/SkipList.h)
