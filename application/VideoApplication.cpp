//
// Created by root on 3/17/20.
//

#include "VideoApplication.h"

uploader::VideoApplication::VideoApplication(cppcms::service &srv) : application(srv) {
    dispatcher().assign("/(\\w+)", &VideoApplication::upload, this, 1);
    mapper().assign("vid", "/{1}");
}

void uploader::VideoApplication::upload(std::string id) {
    if (request().request_method() == "POST") {
        auto vid = Vid(id, request().getenv("HTTP_X_VID_RES"), (char *) request().raw_post_data().first,
                       request().raw_post_data().second);
        this->uploaderService << vid;
        spdlog::info(std::string("/vid/") + id + std::string(" submitted to pool"));
        response().status(response().ok);
    } else {
        response().status(response().method_not_allowed);
        spdlog::warn(std::string("/vid/") + id + std::string(" method_not_allowed"));
    }
}
