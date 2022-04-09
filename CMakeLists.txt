cmake_minimum_required(VERSION 3.21)
project(_0M C)

set(CMAKE_C_STANDARD 11)

add_executable(_0M code/main.c code/stack.h code/stack.c code/operations.c code/operations.h code/logger.h)

if (DEBUG_MODE)
    add_definitions(-DDEBUG_MODE=1)
endif (DEBUG_MODE)