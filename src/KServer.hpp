//
//  KServer.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#ifndef KServer_hpp
#define KServer_hpp

#include "KAPI.hpp"

#include <string>
#include <vector>

class KServer {
public:
    // load a server by ip
    KServer(std::string ip, std::string port);

    // setup a preloaded server from server list query
    KServer(GDict *serverStatus);
    ~KServer();

    std::string description;
    std::string name;
    std::string gamemode;
    std::string ip;
    std::string port;

    int playerCount;
    int maxPlayerCount;
    std::string countString();

    bool fav;
    int timesPlayed;

    std::vector<std::string> players;

};

#endif /* KServer_hpp */
