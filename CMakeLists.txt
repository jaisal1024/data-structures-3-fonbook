cmake_minimum_required(VERSION 3.8)
project(data_structures_3_fonbook)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        fonbook.cpp HashDirectory.cpp HashDirectory.h Entry.cpp Entry.h)

add_executable(data_structures_3_fonbook ${SOURCE_FILES})