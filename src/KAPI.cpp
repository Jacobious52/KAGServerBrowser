//
//  KAPI.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#include "KAPI.hpp"

void KAPI::queryJsonAsync(std::string url, std::string name, KAsyncLoaderDelegate *delegate)
{
    queryAsync(KAPI_SERVER + url, name, delegate);
}

void KAPI::queryAsync(std::string url, std::string name, KAsyncLoaderDelegate *delegate)
{
    ofLogNotice("KAPI", "fetch async: " + url);
    new KAsyncLoader(url, name, delegate);
}

GDict *KAPI::queryJson(std::string url)
{
    int retryCount = 0;
    GDict *jsonObject = nullptr;

    while (retryCount++ < 3)
    {
        ofHttpResponse resp = ofLoadURL(KAPI_SERVER + url);

        ofLogNotice("KAPI", "fetch: " + KAPI_SERVER + url + " - " + std::to_string(resp.status));

        if (resp.status == 200)
        {
            ofLogVerbose("KAPI", "resp json:\n" + resp.data.getText());

            jsonObject = KAPI::toJson(resp.data);
            break;
        }
        else
        {
            ofLogError("KAPI", "error message: " + resp.error);
            ofLogWarning("KAPI", "retrying " + std::to_string(3- retryCount) + " more times");
        }
        
    }
    
    return jsonObject;
}
