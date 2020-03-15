//
// Created by root on 3/14/20.
//

#include "UploaderApplication.h"

void uploader::uploader::upload(std::string id){
    if(request().request_method()=="POST") {
        auto vid = Vid(id,request().getenv("HTTP_X_VID_RES"),(char *)request().raw_post_data().first,request().raw_post_data().second);
        response().status(response().ok);
    } else{
        response().status(response().method_not_allowed);
    }
}

uploader::uploader::uploader(cppcms::service &s) : cppcms::application(s) {
    dispatcher().assign("/vid/(\\w+)", &uploader::uploader::upload, this,1);
    mapper().assign("vid","/vid/{1}");
    mapper().root("/");
}