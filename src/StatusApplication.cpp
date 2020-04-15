#include "uploader/StatusApplication.h"

uploader::StatusApplication::StatusApplication(cppcms::service &srv) : application(srv) {
    dispatcher().assign("/(\\w+)", &StatusApplication::get, this, 1);
    mapper().assign("status", "/{1}");
}

void uploader::StatusApplication::get(std::string id) {
    if (request().request_method() == "GET") {
        if (this->statusService[id] == Status::PROCESSING)
            response().status(102);
        if (this->statusService[id] == Status::ERROR)
            response().status(response().unsupported_media_type);
        if (this->statusService[id] == Status::SUCCESS)
            response().status(response().ok);
    } else {
        response().status(response().method_not_allowed);
        spdlog::warn(std::string("/status/") + std::string(" method_not_allowed"));
    }
}
