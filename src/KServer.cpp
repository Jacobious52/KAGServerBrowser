//
//  KServer.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#include "KServer.hpp"

KServer::KServer(std::string ip_, std::string port_)
{
    ip = ip_;
    port = port_;

    auto json = KAPI::queryJson(KAPI::serverStatus(ip, port));

    if (json == nullptr)
    {
        ofLogError("KServer", "json object null");
        return;
    }

    auto status = GDictFromDict(json, "serverStatus");
    if (status == nullptr)
    {
        ofLogError("KServer", "server does not contain status dict");
        return;
    }

    // load info

    name = GStringFromDict(status, "serverName")->value;
    description = GStringFromDict(status, "description")->value;
    gamemode = GStringFromDict(status, "gameMode")->value;
    playerCount = GNumberFromDict(status, "currentPlayers")->asInt();
    maxPlayerCount = GNumberFromDict(status, "maxPlayers")->asInt();

    //load players

    auto playersArray = GArrayFromDict(status, "playerList");

    for (auto &playerDict : playersArray->value)
    {
        std::string username = GStringFromDict(playerDict, "username")->value;
        players.push_back(username);
    }

    json->free();

    fav = false;
    timesPlayed = 0;
}

KServer::KServer(GDict *serverStatus)
{
    if (serverStatus == nullptr)
    {
        ofLogError("KServer", "server does not contain status dict");
        return;
    }

    // load info

    ip = GStringFromDict(serverStatus, "serverIPv4Address")->value;
    port = std::to_string(GNumberFromDict(serverStatus, "serverPort")->asInt());
    name = GStringFromDict(serverStatus, "serverName")->value;
    description = GStringFromDict(serverStatus, "description")->value;
    gamemode = GStringFromDict(serverStatus, "gameMode")->value;
    playerCount = GNumberFromDict(serverStatus, "currentPlayers")->asInt();
    maxPlayerCount = GNumberFromDict(serverStatus, "maxPlayers")->asInt();

    //load players

    auto playersArray = GArrayFromDict(serverStatus, "playerList");

    for (auto &playerString : playersArray->value)
    {
        std::string username = playerString->as<GString>()->value;
        players.push_back(username);
    }

    fav = false;
    timesPlayed = 0;
}

std::string KServer::countString()
{
    return std::to_string(playerCount) + "/" + std::to_string(maxPlayerCount);
}

KServer::~KServer()
{}