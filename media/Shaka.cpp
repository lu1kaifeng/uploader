//
// Created by root on 3/14/20.
//

#include "Shaka.h"
#include <iostream>
#include <utility>
using namespace uploader;
InStream::InStream(boost::filesystem::path sourceMedia,
std::string streamType,
boost::filesystem::path destination) {
    this->sourceMedia = std::move(sourceMedia);
    this->streamType = std::move(streamType);
    this->destination = std::move(destination);
}

InStream::InStream(std::string streamType, const boost::filesystem::path& destination) {
    this->streamType = std::move(streamType);
    this->destination = std::move(destination);
}

std::ostream& operator<<(std::ostream &o,const InStream& stream){
    return o << std::string(" in=")
        << stream.sourceMedia.native()
        << std::string(",stream=")
        << stream.streamType
        << std::string(",output=")
        << stream.destination.native()
        << std::string(" ");
}

Param::Param() = default;

Param::Param(const boost::filesystem::path& mpdOutput) {
    this->mpdOutput = mpdOutput;
}

void Shaka::operator()(const Param& param) {
    std::ostringstream oss;
    for(const auto& stream : this->inStreams){
        oss << stream;
    }
    oss << param;
    oss.flush();
    boost::process::child(this->shaka.native()+" "+oss.str()).wait();
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
