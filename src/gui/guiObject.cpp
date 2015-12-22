#include "gui/guiObject.h"

guiObject::guiObject()
{
    visible = true;
    //ctor
}

guiObject::~guiObject()
{
    //dtor
}

void guiObject::setTransformation(const sf::Transform &transformation)
{
    objectTransform = transformation;

    for ( auto it = childObjects.begin(); it != childObjects.end(); it++)
        (*it)->setParentTransformation(parentTransform * objectTransform);
}

void guiObject::render(sf::RenderWindow &window)
{
    if (visible)
    {
        sf::Transform transformation = parentTransform * objectTransform;

        renderThis(window, transformation);
        for ( auto it = childObjects.begin(); it != childObjects.end(); it++)
            (*it)->render(window);
    }
}


void guiObject::addChild(guiObjectPtr object)
{
    childObjects.push_back(object);
}
