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

        auto packager = shaka::Packager();
        auto packaging_params = shaka::PackagingParams();

        auto stream_descriptors = std::vector<shaka::StreamDescriptor>();

        for (auto &&stream : *streams) {
            auto streamDesc = shaka::StreamDescriptor();
            streamDesc.input = (rawVidPath / stream.transcoded).native();
            streamDesc.stream_selector = stream.streamType;
            streamDesc.output = (rawVidPath / stream.dashOutput).native();
            stream_descriptors.push_back(streamDesc);
        }
        packaging_params.mpd_params.mpd_output = (rawVidPath / boost::filesystem::path("h264.mpd")).native();
        packaging_params.chunking_params.segment_duration_in_seconds = 2;
        packager.Initialize(packaging_params, stream_descriptors);
        packager.Run();
    });
}

uploader::Vid::Vid(const std::string& id,const std::string& res, char *data, unsigned long long len) {
    this->len = len;
    this->data = data;
    this->id = id;
    this->res = res;
}