cmake_minimum_required(VERSION 3.15)
project(uploader)

set(CMAKE_CXX_STANDARD 17)

add_executable(uploader main.cpp media/Shaka.cpp media/Shaka.h media/FFmpeg.cpp media/FFmpeg.h UploaderApplication.cpp UploaderApplication.h service/UploaderService.cpp service/UploaderService.h Component.cpp Component.h application/VideoApplication.cpp application/VideoApplication.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(jwt-cpp/include)
include_directories(spdlog/include)

set(Boost_INCLUDE_DIR /usr/local/include/boost)
find_package(Boost)
target_link_libraries(uploader cppcms)
target_link_libraries(uploader booster)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

target_link_libraries(uploader Threads::Threads)
target_link_libraries(uploader boost_filesystem)
target_link_libraries(uploader boost_system)
target_link_libraries(uploader ${CMAKE_CURRENT_SOURCE_DIR}/spdlog/build/libspdlog.a)