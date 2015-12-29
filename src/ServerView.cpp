//
//  ServerView.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 25/12/2015.
//
//

#include "ServerView.hpp"

void ServerView::update()
{
    for (auto &child : children)
    {
        child->pos.x = pos.x;
        child->pos.y = pos.y;

        if (child->tag == "")
        {
            child->size.x = size.x;
            child->size.y = ofLerp(child->size.y, size.y, 0.20);
        }

        child->update();
    }
}

void ServerView::draw()
{
    UIElement::draw();

    ofPushMatrix();
    ofTranslate(pos);

    // name - top left
    ofSetColor(ofColor::gold);
    bigFont->drawString(server.name, 10, 30);

    ofSetColor(255);
    // gamemode - top right
    font->drawString(server.gamemode, size.x - font->stringWidth(server.gamemode) - 10, 30);

    auto escape = [](std::string str)
    {
        size_t pos = 0;
        do
        {
            pos = str.find("\\n", pos);
            if (pos == std::string::npos)
            {
                break;
            }
            str.replace(pos, 2, "\n");

        } while (pos != std::string::npos);

        return str;
    };

    // descrition - middle left
    font->drawString(escape(server.description), 10, 70);

    // player count - midle right
    bigFont->drawString(server.countString(), size.x - font->stringWidth(server.countString()) - 20, 60);

    // ip:port - top left
    smallFont->drawString(server.ip + ":" + server.port, 10, 48);

    // player list

    if (server.fav && server.players.size() != 0)
    {
        auto newlines = [](std::string str)
        {
            int count = 0;
            std::for_each(str.begin(), str.end(), [&count](char c){
                if (c == '\n')
                {
                    count++;
                }
            });
            return count;
        };

        bigFont->drawString("Players", 10, 110 + font->stringHeight(server.description)*newlines(escape(server.description)));

        ofPoint pos = {10, bigFont->stringHeight("Players") + 120 + font->stringHeight(server.description)*newlines(escape(server.description))};

        for (auto &player : server.players)
        {
            if (pos.y > size.y - 60)
            {
                pos.x += 200;
                pos.y = bigFont->stringHeight("Players") + 110 + font->stringHeight(server.description)*newlines(escape(server.description));
            }

#ifdef LOAD_AVATARS
            playerImages[player].draw({pos.x + 120, pos.y - 25});
#endif

            font->drawString(player, pos.x, pos.y);

            pos.y += 50;
        }
    }

    ofPopMatrix();
}

void ServerView::urlResponse(ofHttpResponse &resp)
{
    auto name = resp.request.name;
    if (resp.status == 200)
    {
        if (name.substr(name.size()-5, name.size()) == "+json")
        {
            auto json = KAPI::toJson(resp.data);

            if (json == nullptr)
            {
                ofLogError("ServerView", "json for " + name + " null");
                return;
            }

            auto url = GStringFromDict(json, "small")->value;

            ofLoadURLAsync(url.replace(std::string("https://").size(), std::string("forum.kag2d.com").size(), "forum.thd.vg"), name.substr(0, name.size()-5));
        }
        else
        {
            ofImage avatar;
            avatar.load(resp.data);
            playerImages[name] = avatar;

            ofLogNotice("ServerView", "image for " + name + " loaded ok");
        }
    }
    else if (resp.status == 302)
    {
        ofLogNotice("ServerView", name + " needs redirecting");
    }
    else
    {
        ofLogError("ServerView", name + " failed. " + resp.request.url + " - " + resp.error + " - " + std::to_string(resp.status));
    }

    ofRemoveURLRequest(resp.request.getId());
}

// KAsyncLoader seems to be broken for multiple requests at once
// using raw ofurlfileloader until fixed
/*
void ServerView::asyncLoaderDidFinish(KAsyncLoader *sender, ofHttpResponse &resp)
{
    // read the json and request image url
    auto json = KAPI::toJson(resp.data);

    if (json == nullptr)
    {
        ofLogError("ServerView", "player avatar json null");
        return;
    }

    ofLogNotice("ServerView", "loading jpg for player - " + sender->name);

    auto url = GStringFromDict(json, "small")->value;
    //KAPI::queryAsync(url, sender->name.substr(1, sender->name.size()), this);

    // image fetch sync :(
    auto avatarResp = ofLoadURL(url);

    if (avatarResp.status == 200)
    {
        ofImage avatar;
        avatar.load(avatarResp.data);
        playerImages[sender->name] = avatar;
    }
    else
    {
        ofLogError("ServerView", "failed to load " + sender->name + " jpg");
    }

    json->free();
}

void ServerView::asyncLoaderDidFail(KAsyncLoader *sender)
{
    ofLogVerbose("ServerView", "avatar error for " + sender->name + ". They may not have set avatar yet");
}
*/

void ServerView::toggleFav()
{
    server.fav = !server.fav;
    size.y = server.fav ? 450 : 150;

#ifdef LOAD_AVATARS
    if (server.fav && playerImages.size() == 0)
    {
        for (auto &player : server.players)
        {
            // load a default image
            ofImage profile;
            profile.load("noprofile.jpg");
            playerImages[player] = profile;

            auto url = KAPI_SERVER + "player/" + player + "/avatar/s";
            int id = ofLoadURLAsync(url, player + "+json");
            ofLogNotice("ServerView", "loading json for player - " + player + " - " + url);
        }
    }
#endif
}

void ServerView::mouseReleased(int x, int y, int button)
{
    server.timesPlayed++;
    ofLogNotice("ServerView", server.name + " clicked");

    UIElement::mouseReleased(x, y, button);
}

void ServerView::keyPressed(int key)
{
    switch (key) {
        case 'f':
            toggleFav();
            break;
        case 'r':
        {
            bool fav = server.fav;
            int times = server.timesPlayed;
            server = KServer(server.ip, server.port);
            server.fav = fav;
            server.timesPlayed = times;
            break;
        }
        default:
            break;
    }
}