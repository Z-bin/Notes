cmake_minimum_required(VERSION 3.5)

project(RAII)

set(SOURCES
    mutex.cpp
    main.cpp
)

set(CMAKE_CXX_FLAGS -pthread)

add_executable(RAII ${SOURCES})

target_include_directories(RAII
    PUBLIC
        ${PROJECT_BINARY_DIR}/mutex.h
        ${PROJECT_BINARY_DIR}/mutexlock.h
)

