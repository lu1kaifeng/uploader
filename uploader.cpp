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
#include <fstream>
#include <cstdlib>
namespace uploader{
    class uploader : public cppcms::application {
        public:
            explicit uploader(cppcms::service &s) :
                cppcms::application(s) {
                dispatcher().assign("/vid/(\\w+)", &uploader::upload, this,1);
                mapper().assign("vid","/vid/{1}");
                mapper().root("/");
            }
        private:
            void upload(std::string id){
                if(request().request_method()=="POST") {
                    char * body = (char *)request().raw_post_data().first;
                    unsigned long long size =  request().raw_post_data().second;
                    std::ofstream file(std::string("/var/www/html/")+id+std::string("-frag"));
                    file.write(body,size);
                    file.flush();
                    file.close();
                    system((settings().at("app.bento4").str()+std::string("utils/mp4-dash ")+settings().at("app.www").str()+id+std::string("-frag")+
                        std::string(" -o ")+std::string("/var/www/html/")+id).data());
                    remove((std::string("/var/www/html/")+id+std::string("-frag")).data());
                    response().status(response().ok);
                }
            }
        };
}


int main(int argc,char ** argv)
{
    try {
        cppcms::service app(argc,argv);
        app.applications_pool().mount(cppcms::applications_factory<uploader::uploader>());
        app.run();
    }
    catch(std::exception const &e) {
        std::cerr<<e.what()<<std::endl;
    }
}
