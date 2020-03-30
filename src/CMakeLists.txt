add_executable(uploader_app Component.cpp UploaderApplication.cpp UploaderService.cpp VideoApplication.cpp main.cpp)
add_subdirectory(media)
target_link_libraries(uploader_app uploader_media Threads::Threads boost_filesystem boost_system cppcms booster)