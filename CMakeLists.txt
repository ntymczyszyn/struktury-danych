cmake_minimum_required(VERSION 3.22)
project(struktury_danych)

set(CMAKE_CXX_STANDARD 14)


set(SOURCES
        main.cpp
        src/AVLtree.cpp
        src/SkipList.cpp
        src/Node_S.cpp
        src/Node.cpp
        )
set(HEADERS
        include/AVLtree.h
        include/SkipList.h
        include/Node_S.h
        include/Node.h
        )

add_executable(struktury_danych ${SOURCES} ${HEADERS})
