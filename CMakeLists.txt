# Specify minimum CMake version and project name
#
cmake_minimum_required(VERSION 3.0)
project(Scrabble.AI VERSION 0.1.0)


include(CTest)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
#
# CMake setup
#
set(CMAKE_CXX_STANDARD 11)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_VERBOSE_MAKEFILE 0) # 1 should be used for debugging
set (CMAKE_SUPPRESS_REGENERATION TRUE) # Suppresses ZERO_CHECK

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")

if(MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W4")
  set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall")
endif()


message("Generated with config types: ${CMAKE_CONFIGURATION_TYPES}")


# Set include paths for header files
#
include_directories (src/
                    # Add More Direct. Here if needed.
                    src/Board/
                    src/Board/Board_and_tiles/
                    src/Board/Board_and_tiles/Board/Board_and_tiles/
                    src/GuiInterface/
                    src/MoveGeneration/
                    src/SharedClasses/
                    src/Communication/
                    )

#
# Add files
#
file (GLOB_RECURSE PROJECT_HEADERS src/*.hpp
                                   src/*.h)
file (GLOB_RECURSE PROJECT_SOURCES src/*.cpp
                                   src/*.cxx
                                   src/*.cc
                                   src/*.c
                                   src/MoveGeneration/Dict.txt)
file (GLOB         PROJECT_CONFIGS CMakeLists.txt)

#
# Organizing files
#
source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})
source_group ("vendors" FILES ${VENDORS_SOURCES})

#
# Set executable and target link libraries
#
# configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/MoveGeneration/Dict.txt
#     ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/src/MoveGeneration/Dict.txt
     DESTINATION ${CMAKE_BINARY_DIR}/Scrabble.AI/Debug)

add_definitions (-DGLFW_INCLUDE_NONE
                 -DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
                                ${COMMON_SOURCES} ${COMMON_HEADERS}
                                ${PROJECT_CONFIGS} ${VENDORS_SOURCES})
#target_link_libraries (${PROJECT_NAME})
set_target_properties (${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})




