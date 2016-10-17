cmake_minimum_required(VERSION 3.6)
project(consoleChat)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES consoleChat.c serverTools.c chatServer.c serverTools.h)
add_executable(consoleChat ${SOURCE_FILES})