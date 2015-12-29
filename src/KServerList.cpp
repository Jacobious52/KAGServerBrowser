//
//  KServerList.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 23/12/2015.
//
//

#include "KServerList.hpp"
#include "KAPI.hpp"
#include "CSVReader.h"

#include <algorithm>

KServerList::KServerList() : loaded(false)
{}

KServerList::~KServerList()
{}

void KServerList::loadSettings()
{
    ofLogNotice("KServerList", "loading server settings");

    CSVReader reader(ofToDataPath("servers.csv"));
    if (reader.good())
    {
        for (size_t i = 0; i < reader.rows_size(); ++i)
        {
            auto row = reader[i];

            auto server = std::find_if(servers.begin(), servers.end(), [&row](KServer const &s){
                return s.ip + ":" + s.port == row["ip:port"];
            });

            if (server != servers.end())
            {
                auto toInt = [](std::string s) {
                    std::stringstream ss(s);
                    int i = 0;
                    ss >> i;
                    return i;
                };

                server->fav = (bool)toInt(row["fav"]);
                server->timesPlayed = toInt(row["times"]);
            }
        }
    }
}

void KServerList::save()
{
    if (servers.size() == 0)
    {
        return;
    }

    ofLogNotice("KServerList", "saving servers");

    std::stringstream ss;
    ss << "ip:port,fav,times\n";

    for (auto &server : servers)
    {
        ss << server.ip << ":" << server.port << "," << server.fav << "," << server.timesPlayed << "\n";
    }

    ofFile file;
    file.open(ofToDataPath("servers.csv"), ofFile::WriteOnly, false);
    file << ss.str();
    file.close();

}

void KServerList::reload()
{
    save();

    loaded = false;
    servers.clear();

#ifndef TEST_OFFLINE
    //GDict *json = KAPI::queryJson("servers/current/1");
    KAPI::queryJsonAsync("servers/current/1", "serverload", this);
    ofLogNotice("KServerList", "starting async query");
#else
    ofLogNotice("KServerList", "loading from test_servers.json");
    auto json = GDictMake();
    ofFile testFile(ofToDataPath("test_servers.json"));
    testFile >> json;
    testFile.close();

    if (json == nullptr)
    {
        ofLogError("kserverlist", "json object null");
        return;
    }

    auto serversListArray = GArrayFromDict(json, "serverList");
    for (auto &serverDict : serversListArray->value)
    {
        KServer server(serverDict->as<GDict>());
        servers.push_back(server);
    }

    json->free();

    loadSettings();

    sort();

    ofLogNotice("KServerList", std::to_string(servers.size()) + " servers found");

    loaded = true;

#endif
}

void KServerList::asyncLoaderDidFinish(KAsyncLoader *sender, ofHttpResponse &resp)
{
    if (sender->name == "serverload")
    {
        auto json = KAPI::toJson(resp.data);

        if (json == nullptr)
        {
            ofLogError("kserverlist", "json object null");
            return;
        }

        auto serversListArray = GArrayFromDict(json, "serverList");
        for (auto &serverDict : serversListArray->value)
        {
            KServer server(serverDict->as<GDict>());
            servers.push_back(server);
        }

        json->free();

        // load in any settings for server fav and times

        loadSettings();

        // sort and fin

        sort();

        ofLogNotice("KServerList", std::to_string(servers.size()) + " servers found");

        loaded = true;
    }

    if (sender != nullptr)
    {
        delete sender;
    }
}

void KServerList::asyncLoaderDidFail(KAsyncLoader *sender)
{
    ofLogError("KServerList", "async loaded did fail");
    loaded = true;

    if (sender != nullptr)
    {
        delete sender;
    }
}

void KServerList::sort()
{
    std::sort(servers.begin(), servers.end(), [](KServer const &a, KServer const &b)
    {
        if (a.fav && !b.fav)
        {
            return true;
        }
        else if (!a.fav && b.fav)
        {
            return false;
        }

        if (a.timesPlayed == a.timesPlayed)
        {
            return a.playerCount > b.playerCount;
        }
        else
        {
            return a.timesPlayed > b.timesPlayed;
        }
    });
}