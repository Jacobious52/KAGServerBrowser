#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup()
{
    //ofSetLogLevel(OF_LOG_VERBOSE);

    // setup window

    ofSetWindowTitle("Jacobious's KAG Server Browser");
    ofSetVerticalSync(true);
    ofSetCircleResolution(64);
    ofBackgroundHex(0x334E17);

    font.load("AveriaSerif.ttf", 12);
    bigFont.load("AveriaSerif-Bold.ttf", 16);
    smallFont.load("AveriaSerif.ttf", 8);

    // setup gui
    gifIndex = 0;
    gifCounter = 0;
    for (int i = 0; i < 63; ++i)
    {
        ofImage gif;
        gif.load("loading/loading_" + ofToString(i) + ".png");
        loadingGif.push_back(gif);
    }

    gui.pos = {0,0};
    gui.size = {static_cast<float>(ofGetWidth()), static_cast<float>(ofGetHeight())};

    gui.zOrder = 0;

    gui.add(new Image("background.png", {0,0}));
    gui.find<Image>("background.png")->zOrder = -1;
    gui.add(new Image("title.png", {10,10}));
    gui.add(new Button("Refresh Servers", {static_cast<float>(ofGetWidth() - 210), 10}, {200, 75}, 0x5A6658, font, this));
    gui.add(new Listbox("servers", {10, gui.find<Image>("title.png")->size.y}, {static_cast<float>((ofGetWidth()-20)), static_cast<float>((ofGetHeight()-10))-(gui.find<Image>("title.png")->size.y + 10)}, 0x5A6658, font));

    // load server gui
    buttonClicked(gui.find<Button>("Refresh Servers"));
}

void ofApp::exit()
{
    servers.save();
}

void ofApp::buttonClicked(Button *sender)
{
    if (sender->tag == "Refresh Servers")
    {
        ready = false;
        gui.find<Button>("Refresh Servers")->hidden = true;

        for (auto &child : gui.find<Listbox>("servers")->children)
        {
            delete child;
        }
        gui.find<Listbox>("servers")->children.clear();

        servers.reload();

        // wait for return async

        gui.find<Listbox>("servers")->scroll = 0;
    }
}

void ofApp::addServer(UIElement *elem)
{
    gui.find<Listbox>("servers")->add(elem);
}

//--------------------------------------------------------------
void ofApp::update()
{
    // layout
    Image *bg = gui.find<Image>("background.png");
    bg->size = {static_cast<float>(ofGetWidth()), (bg->size.y/bg->size.x)*ofGetWidth()};

    gui.find<Listbox>("servers")->size = {static_cast<float>(ofGetWidth()-20), static_cast<float>(ofGetHeight()-(20+gui.find<Image>("title.png")->size.y))};

    gui.find<Button>("Refresh Servers")->pos.x = ofGetWidth() - 210;

    gui.update();


    // async server check

    if (servers.loaded && !ready)
    {
        for (auto &server : servers.servers)
        {
            addServer(new ServerView(server, bigFont, font, smallFont));
        }
        ready = true;
        gui.find<Button>("Refresh Servers")->hidden = false;
    }
}

//--------------------------------------------------------------
void ofApp::draw()
{
    ofEnableAlphaBlending();
    ofSetColor(255);

    gui.draw();

	smallFont.drawString("Press 'F' on a server to toggle favourite", 10, gui.find<Listbox>("servers")->pos.y - 10);

    if (servers.servers.size() == 0 && ready)
    {
        bigFont.drawString("No Servers Found :(", ofGetWidth()/2 - bigFont.stringWidth("No Servers Found :(")/2, ofGetHeight()/2 - 100);
    }

    if (!servers.loaded && !ready)
    {
        bigFont.drawString("Loading Servers..", ofGetWidth()/2 - bigFont.stringWidth("Loading Servers..")/2, 200 + ofGetHeight()/2);

        gifCounter = ++gifCounter % 2;

        if (gifCounter == 0)
        {
            gifIndex = ++gifIndex % 63;
        }

        ofEnableBlendMode(OF_BLENDMODE_ADD);
        ofSetColor(ofColor::fromHex(0x5A6658));
        loadingGif[62 - gifIndex].draw(ofGetWidth()/2 - loadingGif[0].getWidth()/2, 20);
        ofDisableBlendMode();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
    gui.keyPressed(key);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
    if (gui.find<Listbox>("servers")->inside({static_cast<float>(x), static_cast<float>(y)}))
    {
        gui.find<Listbox>("servers")->mouseScrolled(x, y, scrollX, scrollY);
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{
    gui.mouseMoved(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{
    gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
    ofLogVerbose() << "main: " << x << ", " << y;
    gui.mousePressed(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{
    gui.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y)
{
    gui.mouseLeft();
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{
    
}
