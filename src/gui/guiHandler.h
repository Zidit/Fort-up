#ifndef GUIHANDLER_H
#define GUIHANDLER_H

#include "gui/guiTypedef.h"
#include "gui/guiObject.h"
#include <list>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class guiHandler
{
    public:
        guiHandler();
        virtual ~guiHandler();

        void render(sf::RenderWindow &window);
        void addChild(guiObjectPtr object);

    protected:
    private:
        std::list<guiObjectPtr> childObjects;

};

#endif // GUIHANDLER_H
