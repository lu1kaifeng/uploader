//
// Created by root on 3/14/20.
//
#include <string>
#include <map>
#include <vector>
#include <utility>
#include <memory>
#include <boost/process.hpp>
#include <boost/process/child.hpp>
#include "spdlog/spdlog.h"
#include "media/Shaka.h"
#ifndef UPLOADER_FFMPEG_H
#define UPLOADER_FFMPEG_H
namespace uploader {
    template<typename T>
    struct map_init_helper {
        T &data;

        explicit map_init_helper(T &d) : data(d) {}

        map_init_helper &operator()(typename T::key_type const &key, typename T::mapped_type const &value) {
            data[key] = value;
            return *this;
        }
    };

    template<typename T>
    map_init_helper<T> map_init(T &item) {
        return map_init_helper<T>(item);
    }

    enum VidRes : unsigned short {
        RES360P = 360,
        RES480P = 480,
        RES720P = 720,
        RES1080P = 1080
    };

    class FFmpeg {
    private:
        boost::filesystem::path rootDir;
        boost::filesystem::path fileName;
        boost::filesystem::path ffmpeg;
        VidRes res;
        std::map<std::string , VidRes> resMap;

    public:
        FFmpeg(boost::filesystem::path ffmpeg,boost::filesystem::path rootDir,boost::filesystem::path fileName, const std::string &res);
        std::unique_ptr<std::vector<uploader::InStream>> operator()();
    };

    template<VidRes vidRes>
    boost::process::child transcodeExec(const boost::filesystem::path& ffmpeg,const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

    template<VidRes vidRes>
    std::string transcodeCmd(const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

    template<>
    std::string transcodeCmd<VidRes::RES360P>(const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

    template<>
    std::string transcodeCmd<VidRes::RES480P>(const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

    template<>
    std::string transcodeCmd<VidRes::RES720P>(const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

    template<>
    std::string transcodeCmd<VidRes::RES1080P>(const boost::filesystem::path &rootDir, const boost::filesystem::path &fileName);

}
#endif //UPLOADER_FFMPEG_H
