//
// Created by root on 3/31/20.
//

#include "uploader/AuthService.h"

uploader::AuthService::AuthService(cppcms::application &ctx) : Component(ctx) {

}

uploader::Token uploader::AuthService::operator()(const std::string &token) {
    auto decoded = jwt::decode(token);
    this->verifier.verify(decoded);
    uploader::Token tokenStruct;
    tokenStruct.id = decoded.get_payload_claim("dest").as_string();
    return tokenStruct;
}
