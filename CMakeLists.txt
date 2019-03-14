cmake_minimum_required(VERSION 3.0)

project(Scrabble.AI)

set(${CMAKE_CXX_COMPILER} C:/TDM-GCC-64/bin/gcc.exe CACHE PATH "" FORCE)


#target_include_directories(test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

include_directories ("${PROJECT_SOURCE_DIR}/src/MoveGeneration/")

set(SOURCES src/MoveGeneration/TestGaddag.cpp src/MoveGeneration/LoadNode.cpp src/MoveGeneration/LoadNode.h
src/MoveGeneration/Gaddag.cpp src/MoveGeneration/Gaddag.h
src/MoveGeneration/LoadGaddag.cpp src/MoveGeneration/LoadGaddag.h src/MoveGeneration/Dict.txt)

add_executable(${PROJECT_NAME} ${SOURCES})

# add_library(src/MoveGeneration/ mysqrt.cxx)
#add_subdirectory (src/MoveGeneration/) 
# (${PROJECT_BINARY_DIR})

