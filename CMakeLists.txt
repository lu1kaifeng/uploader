cmake_minimum_required(VERSION 3.15)
project(uploader)

set(CMAKE_CXX_STANDARD 11)

add_executable(uploader uploader.cpp)

find_package(duktape CONFIG REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(uploader cppcms)
target_link_libraries(uploader booster)

