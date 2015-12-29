//
//  KAsyncLoader.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 26/12/2015.
//
//

#ifndef KAsyncLoader_hpp
#define KAsyncLoader_hpp

#include "ofMain.h"

class KAsyncLoader;

class KAsyncLoaderDelegate
{
public:
    virtual void asyncLoaderDidFinish(KAsyncLoader *sender, ofHttpResponse &resp) = 0;
    virtual void asyncLoaderDidFail(KAsyncLoader *sender) = 0;
};

class KAsyncLoader
{
public:
    KAsyncLoader(std::string url_, std::string name_, KAsyncLoaderDelegate *delegate_) : url(url_), name(name_), delegate(delegate_)
    {
        ofRegisterURLNotification(this);

        ofLoadURLAsync(url, name);
    }

    ~KAsyncLoader()
    {
        ofUnregisterURLNotification(this);
    }

    void urlResponse(ofHttpResponse &resp);

    KAsyncLoaderDelegate *delegate;

    std::string url;
    std::string name;
};

#endif /* KAsyncLoader_hpp */
