//
// Created by root on 3/14/20.
//
#include <cppcms/http_context.h>
#include <cppcms/application.h>
#include <cppcms/json.h>
#ifndef UPLOADER_COMPONENT_H
#define UPLOADER_COMPONENT_H


class Component {
protected:
    cppcms::application& ctx;
    explicit Component(cppcms::application &ctx);
};


#endif //UPLOADER_COMPONENT_H
