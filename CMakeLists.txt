cmake_minimum_required(VERSION 3.3)
project(SPM_project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -O3")

set(SOURCE_FILES
        Token.cpp
        Token.h
        Graph.cpp
        Graph.h
        GraphRepository.cpp
        GraphRepository.h
        Interpreter.cpp
        Interpreter.h
        SyncCout.cpp
        SyncCout.h
        ThreadPool.cpp
        ThreadPool.h
        InterpreterFactory.cpp
        InterpreterFactory.h)


add_executable(example main.cpp ${SOURCE_FILES})

add_executable(example_no_print main.cpp ${SOURCE_FILES})
target_compile_definitions(example_no_print PRIVATE NO_PRINT)

add_executable(example_mic main.cpp ${SOURCE_FILES})
set_target_properties(example_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(example_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(example_mic PRIVATE NO_PRINT)
add_custom_command(TARGET example_mic POST_BUILD COMMAND scp example_mic mic1:)



add_executable(busy_test busy_test.cpp ${SOURCE_FILES})

add_executable(busy_test_no_print busy_test.cpp ${SOURCE_FILES})
target_compile_definitions(busy_test_no_print PRIVATE NO_PRINT)

add_executable(busy_test_mic busy_test.cpp ${SOURCE_FILES})
set_target_properties(busy_test_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(busy_test_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(busy_test_mic PRIVATE NO_PRINT)
add_custom_command(TARGET busy_test_mic POST_BUILD COMMAND scp busy_test_mic mic1:)


add_executable(free_test free_test.cpp ${SOURCE_FILES})

add_executable(free_test_no_print free_test.cpp ${SOURCE_FILES})
target_compile_definitions(free_test_no_print PRIVATE NO_PRINT)

add_executable(free_test_mic free_test.cpp ${SOURCE_FILES})
set_target_properties(free_test_mic PROPERTIES COMPILE_FLAGS "-mmic" )
set_target_properties(free_test_mic PROPERTIES LINK_FLAGS "-mmic" )
target_compile_definitions(free_test_mic PRIVATE NO_PRINT)
add_custom_command(TARGET free_test_mic POST_BUILD COMMAND scp free_test_mic mic1:)



