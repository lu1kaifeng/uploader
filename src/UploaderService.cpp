//
// Created by root on 3/14/20.
//

#include "uploader/UploaderService.h"

uploader::UploaderService::UploaderService(cppcms::application &ctx) : Component(ctx) {
    this->httpdRoot = boost::filesystem::path(Component::ctx.settings().at("app.www").str());
    this->shaka =  boost::filesystem::path(Component::ctx.settings().at("app.shaka").str());
    this->ffmpeg = boost::filesystem::path(Component::ctx.settings().at("app.ffmpeg").str());
}

uploader::UploaderService &uploader::UploaderService::operator<<(const uploader::Vid &vid) {
    boost::asio::post(*this->pool, [=]() {
        auto rawVidPath = this->httpdRoot / boost::filesystem::path(vid.id);
        boost::filesystem::create_directory(rawVidPath);
        auto ofs = std::ofstream((rawVidPath / boost::filesystem::path("raw.mp4")).native());
        ofs.write(vid.data, vid.len);
        ofs.flush();
        ofs.close();
        auto ffmpegExec = uploader::FFmpeg(this->ffmpeg, rawVidPath, boost::filesystem::path("raw.mp4"), vid.res);
        auto streams = ffmpegExec();
        auto shakaExec = uploader::Shaka(this->shaka);
        for (auto &&stream : *streams) {
            stream.sourceMedia = rawVidPath / boost::filesystem::path("raw.mp4");
            stream.destination = rawVidPath / stream.destination;
            shakaExec << stream;
        }
        auto param = uploader::Param();
        param.mpdOutput = rawVidPath / param.mpdOutput;
        shakaExec(param);
    });
}

uploader::Vid::Vid(const std::string& id,const std::string& res, char *data, unsigned long long len) {
    this->len = len;
    this->data = data;
    this->id = id;
    this->res = res;
}