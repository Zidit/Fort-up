#ifndef GUITOOLBAR_H
#define GUITOOLBAR_H

#include <SFGUI/SFGUI.hpp>
#include <glm/glm.hpp>

class guiToolBar
{
    public:
        guiToolBar();
        virtual ~guiToolBar();

        void initialize(sfg::Desktop *desktop);

    protected:
    private:
        sfg::Image::Ptr stone;
        sfg::Image::Ptr grass;
        sfg::Box::Ptr box;
        sfg::Window::Ptr window_gui;
        sf::Image imgGrass;
        sf::Image imgStone;

};


#endif // GUITOOLBAR_H
