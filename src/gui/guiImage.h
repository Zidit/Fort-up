#ifndef GUIIMAGE_H
#define GUIIMAGE_H

#include <gui/guiObject.h>
#include <string>
#include "resourceHandler.h"
#include "gui/guiTypedef.h"

class guiImage : public guiObject
{
    public:
        guiImage(const std::string &file);
        virtual ~guiImage();
    protected:
    private:
        void renderThis(sf::RenderWindow &window, const sf::Transform &transformation);
        texturePtr image;
        std::unique_ptr<sf::Sprite> sprite;
};

#endif // GUIIMAGE_H
