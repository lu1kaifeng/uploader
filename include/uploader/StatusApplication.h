#include <cppcms/service.h>
#include <cppcms/application.h>
#include <cppcms/applications_pool.h>
#include <cppcms/cache_interface.h>
#include <iostream>
#include <string>
#include <cppcms/http_request.h>
#include <cppcms/http_context.h>
#include <cppcms/http_response.h>
#include <cppcms/url_dispatcher.h>
#include <cppcms/url_mapper.h>
#include <uploader/UploaderService.h>
#include <uploader/AuthService.h>
#include "spdlog/spdlog.h"
#include "uploader/StatusService.h"
#include "jwt-cpp/jwt.h"

namespace uploader {
    class StatusApplication : public cppcms::application {
    public:
        explicit StatusApplication(cppcms::service &srv);

        Status operator()(std::string);

    private:
        StatusService statusService = StatusService(*this);

        void get(std::string);
    };
}