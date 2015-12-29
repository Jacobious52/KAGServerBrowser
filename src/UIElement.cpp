//
//  UIElement.cpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 24/12/2015.
//
//

#include "UIElement.hpp"
#include <algorithm>


void UIElement::draw()
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            child->draw();
        }
    }
}

void UIElement::update()
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {

            child->update();
        }
    }
}

void UIElement::mousePressed(int x, int y, int button)
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            if (child->inside({static_cast<float>(x), static_cast<float>(y)}))
            {
                ofLogVerbose() << "uielem: " << x << ", " << y;
                child->mousePressed(x, y, button);
            }
        }
    }
}

void UIElement::mouseReleased(int x, int y, int button)
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            if (child->inside({static_cast<float>(x), static_cast<float>(y)}))
            {
                child->mouseReleased(x, y, button);
            }
        }
    }
}

void UIElement::mouseDragged(int x, int y, int button)
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            if (child->inside({static_cast<float>(x), static_cast<float>(y)}))
            {
                child->mouseDragged(x, y, button);
            }
        }
    }
}

void UIElement::mouseMoved(int x, int y)
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            if (child->inside({static_cast<float>(x), static_cast<float>(y)}))
            {
                child->mouseMoved(x, y);
            }
            else
            {
                child->mouseLeft();
            }
        }
    }
}

void UIElement::mouseLeft()
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            child->mouseLeft();
        }
    }
}

void UIElement::keyPressed(int key)
{
    for (auto &child : children)
    {
        if (!child->hidden)
        {
            if (child->inside({static_cast<float>(ofGetMouseX()), static_cast<float>(ofGetMouseY())}))
            {
                child->keyPressed(key);
            }
        }
    }
}

void UIElement::add(UIElement *element)
{
    children.push_back(element);
    std::sort(children.begin(), children.end(), [](UIElement *a, UIElement *b)
              {
                  return a->zOrder < b->zOrder;
              });
}

UIElement *UIElement::operator[](size_t index)
{
    return children[index];
}

bool UIElement::inside(ofPoint p)
{
    return ((p.x > pos.x && p.x < pos.x + size.x) && (p.y > pos.y && p.y < pos.y + size.y));
}


std::vector<UIElement *>::iterator UIElement::begin()
{
    return children.begin();
}

std::vector<UIElement *>::iterator UIElement::end()
{
    return children.end();
}

