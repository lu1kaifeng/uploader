//
// Created by root on 3/14/20.
//
#include <string>
#include <vector>
#include <memory>
#include <utility>
#include <sstream>
#include <boost/process.hpp>
#include <boost/process/child.hpp>
#ifndef UPLOADER_SHAKA_H
#define UPLOADER_SHAKA_H
namespace uploader {
    class InStream {
    public:
        boost::filesystem::path sourceMedia;
        std::string streamType;
        boost::filesystem::path destination;

        InStream(boost::filesystem::path sourceMedia,
                 std::string streamType,
                 boost::filesystem::path destination);

        InStream(std::string streamType,
                 const boost::filesystem::path& destination);
    };

    class Param {
    public:
        boost::filesystem::path mpdOutput = "h264.mpd";

        Param();

        explicit Param(const boost::filesystem::path& mpdOutput);
    };

    class Shaka {
    private:
        std::vector<InStream> inStreams;
        boost::filesystem::path shaka;
    public:

        Shaka &operator<<(InStream &in);

        void operator()(const Param& param);

        explicit Shaka(boost::filesystem::path shaka);
    };

}
std::ostream &operator<<(std::ostream &o, const uploader::InStream &stream);

std::ostream &operator<<(std::ostream &o, const uploader::Param &param);
#endif //UPLOADER_SHAKA_H
