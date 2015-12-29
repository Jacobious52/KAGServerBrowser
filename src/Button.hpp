//
//  Button.h
//  VARVA
//
//  Created by Jacob Gonzalez on 25/06/2015.
//
//

#ifndef Button_hpp
#define Button_hpp

#include "UIElement.hpp"
#include <string>
#include <functional>

class Button;

class ButtonDelegate
{
public:
    virtual void buttonClicked(Button *sender) = 0;
};

class Button : public UIElement
{
public:

    Button(std::string name_, ofPoint pos, ofPoint size, int color, ofTrueTypeFont &font, ButtonDelegate *delegate_)
    : UIElement(pos, size, name_), name(name_), _color(ofColor::fromHex(color)), _font(&font), delegate(delegate_), _circleRadius(0), _growRadius(false)
    {
        setColor(ofColor::fromHex(color));
    }

    virtual ~Button()
    {}

    void update();
    void draw();

    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseDragged(int x, int y, int button);
    void mouseMoved(int x, int y );
    void mouseLeft();

    ofColor getColor() const;
    void setColor(ofColor color);

    std::string name;

    ButtonDelegate *delegate;

    void setFont(ofTrueTypeFont &font);

private:
    ofColor _color;
    ofColor _restColor;
    ofColor _hoverColor;
    ofColor _circleColor;

    ofTrueTypeFont *_font;

    // Material Design click
    ofPoint _clickPos;
    float _circleRadius;
    bool _growRadius;
};

#endif