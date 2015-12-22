#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include <memory>
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "gui/guiTypedef.h"

class guiObject
{
    public:
        guiObject();
        virtual ~guiObject();

        void render(sf::RenderWindow &window);
        void addChild(guiObjectPtr object);
        void setVisible(const bool visible) {this->visible = visible;}
        void setTransformation(const sf::Transform &transformation);
        void setParentTransformation(const sf::Transform &transformation) {parentTransform = transformation;}

    protected:
    private:
        sf::Transform objectTransform;
        sf::Transform parentTransform;
        std::list<guiObjectPtr> childObjects;
        bool visible;
        virtual void renderThis(sf::RenderWindow &window, const sf::Transform &transformation) = 0;

};


#endif // GUIOBJECT_H
