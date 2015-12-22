#include "resourceHandler.h"
#include <iostream>

resourceHandler resources;
const std::string pathImages = "./res/images/";

resourceHandler::resourceHandler()
{
    //ctor
}

resourceHandler::~resourceHandler()
{
    //dtor
}

imagePtr resourceHandler::getImage(std::string const &fileName)
{
    // Find if image is already loaded and return it
    auto it = images.find(fileName);
    if ( it != images.end( ) )
        return it->second;
    else {

        //Image was not loaded. Create new image and add it to map
        imagePtr newImage(new sf::Image());
        images.insert( std::make_pair( fileName, newImage) );

        //Load image from file
        if (!newImage->loadFromFile(pathImages + fileName))
        {
            //Image was not found. Create deafult image
            newImage->create(1,1, sf::Color::Magenta);
        }

        return newImage;
    }

}

texturePtr resourceHandler::getTexture(std::string const &fileName)
{
    auto it = textures.find(fileName);
    if ( it != textures.end( ) )
        return it->second;
    else {

        imagePtr img = getImage(fileName);

        texturePtr newTexture(new sf::Texture());
        newTexture->loadFromImage(*img);
        textures.insert( std::make_pair( fileName, newTexture) );

        return newTexture;
    }

}
