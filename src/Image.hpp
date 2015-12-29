//
//  Image.hpp
//  KAGServers
//
//  Created by Jacob Gonzalez on 24/12/2015.
//
//

#ifndef Image_hpp
#define Image_hpp

#include "UIElement.hpp"

class Image : public UIElement
{
public:

    Image(std::string filename_, ofPoint pos_) : UIElement(), filename(filename_)
    {
        tag = filename_;
        image.load(filename);
        pos = pos_;
        size = {image.getWidth(), image.getHeight()};
    }

    virtual ~Image()
    {}

    void draw();

    std::string filename;
    ofImage image;
};


#endif /* Image_hpp */
