add_library(uploader_media FFmpeg.cpp Shaka.cpp)
target_link_libraries(uploader_media packager)