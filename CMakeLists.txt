cmake_minimum_required(VERSION 3.15)
project(uploader)

set(CMAKE_CXX_STANDARD 17)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/include)

set(Boost_INCLUDE_DIR /usr/local/include/boost)
find_package(Boost)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib/lib)
find_package(OpenSSL)


add_subdirectory(test)
add_subdirectory(src)


