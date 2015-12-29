//
//  Listbox.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 24/12/2015.
//
//

#include "Listbox.hpp"

void Listbox::update()
{
    thumb->pos = {pos.x + size.x - 20, pos.y + 5 + scroll};
    thumb->size.y = ofClamp(size.y/(children.size()+1), 30, size.y);

    UIElement::update();
    thumb->update();
}

void Listbox::draw()
{
    // clip to the list box

    glScissor(pos.x, ofGetHeight() - pos.y - size.y, size.x, size.y);
    glEnable(GL_SCISSOR_TEST);

    ofSetColor(color.r, color.g, color.b, 200);
    ofDrawRectangle(pos, size.x, size.y);

    ofSetColor(ofColor::fromHsb(color.getHue(), color.getSaturation(), color.getBrightness()-30));
    ofDrawRectangle(pos.x + size.x - 20, pos.y + 5, 15, size.y - 10);

    float totalHeight = pos.y + 5;

    for (auto &child : children)
    {
        child->pos = {pos.x + 5, totalHeight - scroll/(size.y - thumb->size.y - 1)*contentHeight()};
        child->size.x = size.x - 30;
        totalHeight += 5 + child->size.y;
    }

    UIElement::draw();
    thumb->draw();

    glDisable(GL_SCISSOR_TEST);
}

float Listbox::contentHeight()
{
    float totalHeight = 5;
    for (auto &child : children)
    {
        totalHeight += 5 + child->size.y;
    }
    return totalHeight;
}

void Listbox::mouseScrolled(int x, int y, float scrollX, float scrollY)
{
    scroll += -scrollY*0.2;
    scroll = ofClamp(scroll, 0, size.y - thumb->size.y - 10);
}

void Listbox::mousePressed(int x, int y, int button)
{
    if (thumb->inside({static_cast<float>(x), static_cast<float>(y)}))
    {
        thumb->mousePressed(x, y, button);
        dragging = true;
    }

    UIElement::mousePressed(x, y, button);
}

void Listbox::mouseReleased(int x, int y, int button)
{
    if (thumb->inside({static_cast<float>(x), static_cast<float>(y)}))
    {
        thumb->mouseReleased(x, y, button);
    }

    dragging = false;

    UIElement::mouseReleased(x, y, button);
}

void Listbox::mouseDragged(int x, int y, int button)
{
    if (thumb->inside({static_cast<float>(x), static_cast<float>(y)}))
    {
        thumb->mouseDragged(x, y, button);
        dragging = true;
    }

    if (dragging)
    {
        scroll = ofClamp(y - pos.y - 5, 0, size.y - thumb->size.y - 10);
    }

    UIElement::mouseDragged(x, y, button);
}

void Listbox::mouseMoved(int x, int y)
{
    if (thumb->inside({static_cast<float>(x), static_cast<float>(y)}))
    {
        thumb->mouseMoved(x, y);
    }
    else
    {
        thumb->mouseLeft();
    }

    UIElement::mouseMoved(x, y);
}

void Listbox::mouseLeft()
{
    dragging = false;

    UIElement::mouseLeft();
}
