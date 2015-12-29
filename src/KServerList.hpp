//
//  KServerList.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#ifndef KServerList_hpp
#define KServerList_hpp

//#define TEST_OFFLINE

#include "KServer.hpp"

class KServerList : KAsyncLoaderDelegate
{
public:
    KServerList();
    ~KServerList();

    /// @brief reload the list of servers
    void reload();
    bool loaded;

    void loadSettings();
    void save();
    
    void asyncLoaderDidFinish(KAsyncLoader *sender, ofHttpResponse &resp);
    void asyncLoaderDidFail(KAsyncLoader *sender);

    void sort();

    std::vector<KServer> servers;
};

#endif /* KServerList_hpp */
