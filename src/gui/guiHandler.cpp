#include "gui/guiHandler.h"

guiHandler::guiHandler()
{
    //ctor
}

guiHandler::~guiHandler()
{
    //dtor
}


void guiHandler::render(sf::RenderWindow &window)
{


    for ( auto it = childObjects.begin(); it != childObjects.end(); it++)
        (*it)->render(window);

}


void guiHandler::addChild(guiObjectPtr object)
{
    childObjects.push_back(object);
}
