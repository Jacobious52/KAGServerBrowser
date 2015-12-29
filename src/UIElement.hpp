//
//  UIElement.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 24/12/2015.
//
//

#ifndef UIElement_hpp
#define UIElement_hpp

#include "ofMain.h"

#include <vector>

class UIElement {
public:

    UIElement() : pos(0, 0), size(0, 0), zOrder(0), hidden(false)
    {}
    UIElement(ofPoint pos_, ofPoint size_, std::string tag_) : pos(pos_), size(size_), zOrder(0), tag(tag_), hidden(false)
    {}
    virtual ~UIElement()
    {
        for (auto &child : children)
        {
            delete child;
        }
        children.clear();
    }

    void add(UIElement *element);
    UIElement *operator[](size_t index);
    std::vector<UIElement *>::iterator begin();
    std::vector<UIElement *>::iterator end();

    template <typename T>
    T *find(std::string tag)
    {

        auto it = std::find_if(children.begin(), children.end(), [&](UIElement *c)
        {
            return c->tag == tag;
        });
        return dynamic_cast<T *>(*it);
    }

    ofPoint pos;
    ofPoint size;
    int zOrder;

    std::string tag;

    bool inside(ofPoint p);

    bool hidden;

    virtual void draw();
    virtual void update();

    virtual void mousePressed(int x, int y, int button);
    virtual void mouseReleased(int x, int y, int button);
    virtual void mouseDragged(int x, int y, int button);
    virtual void mouseMoved(int x, int y);
    virtual void mouseLeft();

    virtual void keyPressed(int key);

    std::vector<UIElement *> children;

};

#endif /* UIElement_hpp */
