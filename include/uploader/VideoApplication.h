//
// Created by root on 3/17/20.
//
#include <cppcms/service.h>
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/cache_interface.h>
#include <iostream>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <uploader/UploaderService.h>
#include <uploader/AuthService.h>
#include "spdlog/spdlog.h"
#include "jwt-cpp/jwt.h"

#ifndef UPLOADER_VIDEOAPPLICATION_H
#define UPLOADER_VIDEOAPPLICATION_H

namespace uploader {
    class VideoApplication : public cppcms::application {
    public:
        explicit VideoApplication(cppcms::service &srv);

    private:
        UploaderService uploaderService = UploaderService(*this);
        AuthService authService = AuthService(*this);
        void upload(std::string id);
    };
}


#endif //UPLOADER_VIDEOAPPLICATION_H
