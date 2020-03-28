//
// Created by root on 3/14/20.
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
#include "UploaderService.h"
#include "VideoApplication.h"
#include <fstream>
#include <cstdlib>

#ifndef UPLOADER_UPLOADERAPPLICATION_H
#define UPLOADER_UPLOADERAPPLICATION_H


namespace uploader {
    class UploaderApplication : public cppcms::application {
    public:
        explicit UploaderApplication(cppcms::service &s);
    };
}


#endif //UPLOADER_UPLOADERAPPLICATION_H
