//
// Created by root on 3/14/20.
//

#include "uploader/media/Shaka.h"
#include <iostream>
#include <utility>
using namespace uploader;
InStream::InStream(boost::filesystem::path sourceMedia,
                   std::string streamType,
                   boost::filesystem::path transcoded, boost::filesystem::path dashOutput) {
    this->sourceMedia = std::move(sourceMedia);
    this->streamType = std::move(streamType);
    this->transcoded = std::move(transcoded);
    this->dashOutput = std::move(dashOutput);
}

InStream::InStream(std::string streamType, boost::filesystem::path transcoded, boost::filesystem::path dashOutput) {
    this->streamType = std::move(streamType);
    this->transcoded = std::move(transcoded);
    this->dashOutput = std::move(dashOutput);
}

std::ostream& operator<<(std::ostream &o,const InStream& stream){
    return o << std::string(" in=")
             << stream.sourceMedia.native()
             << std::string(",stream=")
             << stream.streamType
             << std::string(",output=")
             << stream.transcoded.native()
        << std::string(" ");
}

Param::Param() = default;

Param::Param(const boost::filesystem::path& mpdOutput) {
    this->mpdOutput = mpdOutput;
}

void Shaka::operator()(const Param& param) {
    std::ostringstream oss;
    for (const auto &stream : this->inStreams) {
        oss << stream;
    }
    oss << param;
    oss.flush();
    auto child = boost::process::child(this->shaka.native() + " " + oss.str());
    child.wait();
    if (child.exit_code() != 0) {
        spdlog::error(std::string("Shaka Packager returned exit code ") + std::to_string(child.exit_code()) +
                      std::string(" during fragmentation process exited for ") +
                      std::string((param.mpdOutput).native()));
    } else {
        spdlog::info(std::string("Shaka Packager fragmentation process exited successfully for ") +
                     std::string((param.mpdOutput).native()));
    }

}

Shaka::Shaka(boost::filesystem::path shaka) {
    this->shaka = std::move(shaka);
}

Shaka &Shaka::operator<<(InStream &in) {
    this->inStreams.push_back(in);
    return *this;
}

std::ostream &operator<<(std::ostream &o,const Param& param) {
    return o << std::string(" --mpd_output ") << param.mpdOutput.native() << std::string(" ");
}
