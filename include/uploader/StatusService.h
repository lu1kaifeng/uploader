//
// Created by root on 4/14/20.
//
#include "memory"
#include "map"
#include "string"
#include "Component.h"

#ifndef UPLOADER_STATUSSERVICE_H
#define UPLOADER_STATUSSERVICE_H

#endif //UPLOADER_STATUSSERVICE_H
namespace uploader {
    enum Status {
        PROCESSING,
        ERROR,
        SUCCESS
    };

    class StatusService : Component {
    private:
        std::unique_ptr<std::map<std::string, Status>> map = std::make_unique<std::map<std::string, Status>>();
    public:
        explicit StatusService(cppcms::application &ctx);

        void processing(const std::string &);

        void error(const std::string &);

        void finish(const std::string &);

        Status operator[](const std::string &);
    };
}