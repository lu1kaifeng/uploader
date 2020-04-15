add_executable(uploader_app Component.cpp UploaderApplication.cpp UploaderService.cpp VideoApplication.cpp main.cpp AuthService.cpp StatusService.cpp StatusApplication.cpp)
add_subdirectory(media)
target_link_libraries(uploader_app uploader_media Threads::Threads boost_filesystem boost_system cppcms booster packager OpenSSL::Crypto)