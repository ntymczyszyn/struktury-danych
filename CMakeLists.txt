cmake_minimum_required(VERSION 3.22)
project(struktury_danych)

set(CMAKE_CXX_STANDARD 14)


set(SOURCES
        main.cpp
        src/AVLtree.cpp
        src/SkipList.cpp
        src/SNode.cpp
        src/AVLNode.cpp
        )
set(HEADERS
        include/AVLtree.h
        include/SkipList.h
        include/SNode.h
        include/AVLNode.h
        )

add_executable(struktury_danych ${SOURCES} ${HEADERS})

add_executable(tests tests/performance_tests.cpp)