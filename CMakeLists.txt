cmake_minimum_required(VERSION 2.8)

project(codesamples)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -Werror")

include_directories("${PROJECT_SOURCE_DIR}/gtest/googletest/include"
                    "${PROJECT_SOURCE_DIR}/gtest/googletest/"
                    "${PROJECT_SOURCE_DIR}/src")

file(GLOB HEADERS "${PROJECT_SOURCE_DIR}/src/*.h")

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/gtest/googletest/src/gtest-all.cc"
                  "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_link_libraries(${PROJECT_NAME} pthread)
