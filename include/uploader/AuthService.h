//
// Created by root on 3/31/20.
//

#ifndef UPLOADER_AUTHSERVICE_H
#define UPLOADER_AUTHSERVICE_H

#include "Component.h"
#include "jwt-cpp/jwt.h"

namespace uploader {
    struct Token {
        std::string id;
    };

    class AuthService : Component {
    public:
        explicit AuthService(cppcms::application &ctx);

        Token operator()(const std::string &token);

    private:
        jwt::verifier<jwt::default_clock> verifier = jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{Component::ctx.settings().at("app.secret").str()});
    };
}

#endif //UPLOADER_AUTHSERVICE_H
