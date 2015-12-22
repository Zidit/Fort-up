#include "gui/guiImage.h"


guiImage::guiImage(const std::string &file)
{
    //ctor
    image = resources.getTexture(file);
    sprite = std::unique_ptr<sf::Sprite>(new sf::Sprite(*image));
}

guiImage::~guiImage()
{
    //dtor
}

void guiImage::renderThis(sf::RenderWindow &window, const sf::Transform &transformation)
{
    window.draw(*sprite, transformation);
}
