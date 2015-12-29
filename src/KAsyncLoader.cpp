//
//  KAsyncLoader.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 26/12/2015.
//
//

#include "KAsyncLoader.hpp"

void KAsyncLoader::urlResponse(ofHttpResponse &resp)
{
    ofLogNotice("KAsyncLoader", "async response: " + resp.request.name + " == " + name + " : " + resp.request.url + " - " + std::to_string(resp.status));

    if (resp.status == 200 && resp.request.name == name)
    {
        if (delegate)
        {
            delegate->asyncLoaderDidFinish(this, resp);
        }
    }
    else
    {
        if (delegate)
        {
            delegate->asyncLoaderDidFail(this);
        }
    }

    ofRemoveURLRequest(resp.request.getId());
}
