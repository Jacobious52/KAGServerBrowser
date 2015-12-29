//
//  Button.cpp
//  VARVA
//
//  Created by Jacob Gonzalez on 25/06/2015.
//
//

#include "Button.hpp"

void Button::update()
{
    if (_growRadius)
    {
        _circleRadius = ofLerp(_circleRadius, MAX(size.x, size.y), 0.15);
    }
    else
    {
        _circleRadius = ofLerp(_circleRadius, 0, 0.25);
    }

    UIElement::update();
}

void Button::draw()
{
    ofSetColor(_color);
    ofDrawRectangle(pos, size.x, size.y);

    // Material Design
    if (_circleRadius > 0)
    {
        // keep old clipping
        int rect[4];
        bool on = glIsEnabled(GL_SCISSOR_TEST);
        glGetIntegerv(GL_SCISSOR_BOX, rect);

        glScissor(pos.x, ofGetHeight() - pos.y - size.y, size.x, size.y);
        glEnable(GL_SCISSOR_TEST);

        ofSetColor(_circleColor);
        ofDrawCircle(_clickPos, _circleRadius);

        // restore clipping
        glScissor(rect[0], rect[1], rect[2], rect[3]);
        if(!on)
        {
            glDisable(GL_SCISSOR_TEST);
        }
    }

    ofSetColor(255);
    int sizeX = _font->stringWidth(name);
    int sizeY = _font->stringHeight(name);
    _font->drawString(name, pos.x + size.x/2 - sizeX/2, pos.y + size.y/2 + sizeY/2 - 2);

    UIElement::draw();
}

void Button::setFont(ofTrueTypeFont &font)
{
    _font = &font;
}

void Button::mousePressed(int x, int y, int button)
{
    _growRadius = true;
    _clickPos = ofPoint(x, y);

    ofLogVerbose() << "button: " << x << ", " << y;

    UIElement::mousePressed(x, y, button);
}

void Button::mouseReleased(int x, int y, int button)
{
    _growRadius = false;

    if (delegate)
    {
        delegate->buttonClicked(this);
    }

    UIElement::mouseReleased(x, y, button);
}

void Button::mouseDragged(int x, int y, int button)
{
    _clickPos = ofPoint(x, y);

    UIElement::mouseDragged(x, y, button);
}

void Button::mouseMoved(int x, int y )
{
    _color = _color.lerp(_hoverColor, 0.25);

    UIElement::mouseMoved(x, y);
}

void Button::mouseLeft()
{
    if (_growRadius)
    {
        _growRadius = false;
    }

    _color = ofColor(_restColor);

    UIElement::mouseLeft();
}

ofColor Button::getColor() const
{
    return _color;
}

void Button::setColor(ofColor color)
{
    _restColor = color;
    _hoverColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness()+30);
    _circleColor = ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness()+10);
}