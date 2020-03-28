#include <cppcms/service.h>
#include <cppcms/applications_pool.h>
#include <iostream>
#include "uploader/UploaderApplication.h"
#include "jwt-cpp/jwt.h"
#include "spdlog/spdlog.h"

int main(int argc, char **argv) {
    try {
        cppcms::service app(argc, argv);
        app.applications_pool().mount(cppcms::applications_factory<uploader::UploaderApplication>());
        app.run();
    }
    catch (std::exception const &e) {
        std::cerr << e.what() << std::endl;
    }
}
