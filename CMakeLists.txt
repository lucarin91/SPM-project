cmake_minimum_required(VERSION 3.3)
project(SPM_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SOURCE_FILES
        main.cpp
        Token.cpp
        Token.h
        Graph.cpp
        Graph.h
        GraphRepository.cpp
        GraphRepository.h
        Interpreter.cpp
        Interpreter.h
        SyncCout.cpp
        SyncCout.h ThreadPool.cpp ThreadPool.h)

add_executable(SPM_project ${SOURCE_FILES})