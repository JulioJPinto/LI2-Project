cmake_minimum_required(VERSION 3.21)
project(_0M C)

set(CMAKE_C_STANDARD 11)

add_executable(_0M code/main.c code/stack.h code/stack.c code/operations.c code/operations.h code/logger.h code/conversions.c code/conversions.h)

if (DEBUG_MODE)
    add_definitions(-DDEBUG_MODE=1)
endif (DEBUG_MODE)

add_definitions(
        -Wall
        -Wextra
        -pedantic
        -Werror
        -pedantic-errors
        -Wconversion
        -Wimplicit-fallthrough
        -Wuninitialized
        -Wsign-conversion
        -Wfloat-equal
        -Wundef
        -Wshadow
        -Wpointer-arith
        -Wwrite-strings
        -Waggregate-return
        -Wswitch-default
        -Wswitch-enum
        -Wunreachable-code
)