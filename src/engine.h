#ifndef ENGINE_H
#define ENGINE_H

#include "resourcemanager.h"
#include "gameobject.h"
#include "testobject.h"
#include "objectworld.h"
#include "camera.h"
#include "world.h"
#include "worldrender.h"
#include "player.h"
#include "objecthudtest.h"
#include "input.h"
#include "entityPlayer.h"
#include "playerControl.h"

#include "gui/guidebug.h"
#include "gui/guiToolBar.h"

#include "gui/guiHandler.h"
#include "gui/guiImage.h"

#include <string>
#include <vector>
#include <iostream>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

class engine
{
    public:
        engine();
        virtual ~engine();

        bool quit();
        bool initialize(int width, int height);
        void setWindowPointer(sf::RenderWindow *window){ window_ptr = window;}
        void resize(int width, int height);

        void process_input();
        void update(int dt);
        void render();
        void sfmlEvent(sf::Event event);


        static void error(std::string error);
        static void warning(std::string error);


    protected:
    private:

        void addGameObject(gameObject *object);
        void addHudObject(gameObject *object);
        std::vector<gameObject*> gameObjects;
        std::list<gameObject*> hudObjects;

        world gameWorld;
        worldRender gameWorldRender;

      //  player player1;
        entityPlayer player0;
        playerControl *player0Control;

        testObject *testO;

        glm::mat4 perspective;
        glm::mat4 ortho;

        resourceManager resourceMgr;
      //  cameraFPS camera;
        bool end_game;
        bool freeMouse;

        sf::Vector2i lastMousePosition;
        sf::RenderWindow *window_ptr;


        action fm;
        action hit;
        action use;

        guiDebug debug;
        guiToolBar toolBar;

        sfg::Desktop desktop;
        sfg::SFGUI sfgui;
       // inputHandel input;

        guiHandlerPtr gui;

};













#endif // ENGINE_H
