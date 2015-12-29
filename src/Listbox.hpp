//
//  Listbox.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 24/12/2015.
//
//

#ifndef Listbox_hpp
#define Listbox_hpp

#include "UIElement.hpp"
#include "Button.hpp"

class Listbox : public UIElement
{
public:

    Listbox(std::string tag_, ofPoint pos_, ofPoint size_, int color_, ofTrueTypeFont &font_) : UIElement(pos_, size_, tag_), color(ofColor::fromHex(color_)), scroll(0), dragging(false)
    {
        thumb = new Button("", {0, 0}, {15, 30}, color_+0x222222, font_, nullptr);
    }

    virtual ~Listbox()
    {
        delete thumb;
    }

    void update();
    void draw();

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseMoved(int x, int y );
    void mouseLeft();

    void mouseScrolled(int x, int y, float scrollX, float scrollY);

    float contentHeight();

    ofColor color;

    float scroll;

    Button *thumb;

    bool dragging;
};



#endif /* Listbox_hpp */
