cmake_minimum_required(VERSION 3.0.0)
project(Scrabble.ai VERSION 0.1.0)

include(CTest)
enable_testing()

include_directories(
    src/
)

#
# Add files
#
file (GLOB_RECURSE VENDORS_SOURCES vendor/*.hpp
                                   vendor/*.h
                                   vendor/*.cpp
                                   vendor/*.c)

file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
                                   src/*.h)

file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.cxx
                                   src/*.cc
                                   src/*.c)

file (GLOB         PROJECT_CONFIGS CMakeLists.txt)

#
# Organizing files
#
source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                ${PROJECT_CONFIGS} ${VENDORS_SOURCES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
