#include "uploader/StatusService.h"
//
// Created by root on 4/14/20.
//

uploader::StatusService::StatusService(cppcms::application &ctx) : Component(ctx) {

}

void uploader::StatusService::finish(const std::string &id) {
    this->map->erase(id);
}

void uploader::StatusService::error(const std::string &id) {
    this->map->erase(id);
    this->map->insert(std::pair<std::string, uploader::Status>(id, uploader::Status::ERROR));
}

void uploader::StatusService::processing(const std::string &id) {
    this->map->insert(std::pair<std::string, uploader::Status>(id, uploader::Status::PROCESSING));
}

uploader::Status uploader::StatusService::operator[](const std::string &id) {
    if (this->map->find(id) == this->map->end()) {
        return uploader::Status::SUCCESS;
    } else {
        return this->map->find(id)->second;
    }
}
