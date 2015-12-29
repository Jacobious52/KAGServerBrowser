//
//  ServerView.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 25/12/2015.
//
//

#ifndef ServerView_hpp
#define ServerView_hpp

#include "Button.hpp"
#include "Listbox.hpp"
#include "KServer.hpp"

#include <map>

//#define LOAD_AVATARS

class ServerView : public UIElement
{
public:
    ServerView(KServer &server_, ofTrueTypeFont &bigFont_, ofTrueTypeFont &font_, ofTrueTypeFont &smallFont_) : UIElement({0,0}, {0, 150}, server_.name), server(server_), bigFont(&bigFont_), font(&font_), smallFont(&smallFont_)
    {
        //ofRegisterURLNotification(this);

        if (server.fav)
        {
            // toggle fav back to true
            server.fav = false;
            toggleFav();
        }

        add(new Button("", pos, size, 0x5A6658, *font, nullptr));
    }
    virtual ~ServerView()
    {
        //ofUnregisterURLNotification(this);
    }

    KServer &server;

    ofTrueTypeFont *bigFont;
    ofTrueTypeFont *font;
    ofTrueTypeFont *smallFont;

    // KAsyncLoader seems to be broken for multiple requests at once
    // using raw ofurlfileloader until fixed
    /*
    void asyncLoaderDidFinish(KAsyncLoader *sender, ofHttpResponse &resp);
    void asyncLoaderDidFail(KAsyncLoader *sender);
    */

    void urlResponse(ofHttpResponse &resp);

    void update();
    void draw();

    void mouseReleased(int x, int y, int button);

    void toggleFav();

    std::map<std::string, ofImage> playerImages;

    void keyPressed(int key);
};

#endif /* ServerView_hpp */
