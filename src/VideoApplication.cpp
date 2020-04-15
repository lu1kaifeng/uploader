//
// Created by root on 3/17/20.
//

#include "uploader/VideoApplication.h"

uploader::VideoApplication::VideoApplication(cppcms::service &srv) : application(srv) {
    dispatcher().assign("/", &VideoApplication::upload, this);
    mapper().assign("vid", "/");
}

void uploader::VideoApplication::upload() {
    if (request().request_method() == "POST") {
        try {
            auto token = this->authService(request().getenv("HTTP_X_API_KEY"));
            auto vid = Vid(token.id, request().getenv("HTTP_X_VID_RES"), (char *) request().raw_post_data().first,
                           request().raw_post_data().second);
            this->uploaderService << vid;

            spdlog::info(std::string("/vid/") + token.id + std::string(" submitted to pool"));

            response().status(response().ok);
        } catch (jwt::token_verification_exception &exception) {
            response().status(response().unauthorized);
            return;
        }
    } else {
        response().status(response().method_not_allowed);
        spdlog::warn(std::string("/vid") + std::string(" method_not_allowed"));
    }
}
