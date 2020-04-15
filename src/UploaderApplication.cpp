//
// Created by root on 3/14/20.
//

#include "uploader/UploaderApplication.h"

uploader::UploaderApplication::UploaderApplication(cppcms::service &s) : cppcms::application(s) {
    attach(new VideoApplication(s),
           "vid", "/vid{1}", // mapping
           "/vid(/(.*))?", 1);
    attach(new StatusApplication(s), "status", "/status{1}", "/vid(/(.*))?", 1);
    mapper().root("/");
}