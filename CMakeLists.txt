cmake_minimum_required(VERSION 3.0)

project(Scrabble.AI)

set(SOURCE src/MoveGeneration/TestGaddag.cpp)
include_directories(${PROJECT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCE})