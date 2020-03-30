//
// Created by root on 3/14/20.
//

#ifndef UPLOADER_UPLOADERSERVICE_H
#define UPLOADER_UPLOADERSERVICE_H

#include <uploader/Component.h>
#include <boost/filesystem.hpp>
#include <fstream>
#include <memory>
#include "uploader/media/FFmpeg.h"
#include "uploader/media/Shaka.h"
#include "boost/asio/thread_pool.hpp"
#include "packager/packager.h"

namespace uploader {
    struct Vid {
        std::string id;
        std::string res;
        char *data;
        unsigned long long len;

        Vid(const std::string &id, const std::string &res, char *data, unsigned long long len);
    };

    class UploaderService : Component {
    private:
        std::unique_ptr<boost::asio::thread_pool> pool = std::make_unique<boost::asio::thread_pool>(
        );
        boost::filesystem::path httpdRoot, ffmpeg, shaka;
    public:
        explicit UploaderService(cppcms::application &ctx);

        UploaderService &operator<<(const Vid &vid);
    };
}


#endif //UPLOADER_UPLOADERSERVICE_H
