#pragma once

#include "ofMain.h"

#include "KServerList.hpp"
#include "Button.hpp"
#include "Image.hpp"
#include "Listbox.hpp"
#include "ServerView.hpp"

class ofApp : public ofBaseApp, public ButtonDelegate
{
public:
    void setup();
    void exit();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void mouseScrolled(int x, int y, float scrollX, float scrollY);

    void buttonClicked(Button *sender);

    ofTrueTypeFont font;
    ofTrueTypeFont bigFont;
    ofTrueTypeFont smallFont;

    KServerList servers;

    UIElement gui;

    void addServer(UIElement *elem);
    bool ready;

    std::vector<ofImage> loadingGif;
    int gifIndex;
    int gifCounter;

};
