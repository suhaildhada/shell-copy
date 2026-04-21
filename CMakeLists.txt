cmake_minimum_required(VERSION 4.1)
project(shell_copy)

set(CMAKE_CXX_STANDARD 20)

add_executable(shell_copy main.cpp
        commands.h
        commands.cpp
        utils.cpp
        utils.h
        tokenizer.cpp
        tokenizer.h
)
