//
//  KAPI.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#ifndef KAPI_hpp
#define KAPI_hpp

#include "KAsyncLoader.hpp"
#include "Generics.h"
#include "ofMain.h"

#include <sstream>

#define KAPI_SERVER std::string("https://api.kag2d.com/")

class KAPI
{
public:
    static GDict *queryJson(std::string url);

    static void queryJsonAsync(std::string url, std::string name, KAsyncLoaderDelegate *delegate);

    static void queryAsync(std::string url, std::string name, KAsyncLoaderDelegate *delegate);

    static inline std::string serverStatus(std::string ip, std::string port)
    {
        return "server/ip/" + ip + "/port/" + port + "/status";
    }

    static inline GDict *toJson(ofBuffer &buff)
    {
        auto jsonObject = GDictMake();
        std::stringstream ss(buff.getText());
        ss >> jsonObject;
        return jsonObject;
    }

};

#endif /* KAPI_hpp */
