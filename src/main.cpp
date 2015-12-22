
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "engine.h"
#include <SFGUI/SFGUI.hpp>

#include <glm/glm.hpp>

const int screen_width = 800, screen_heigt = 600;
//const int screen_width = 1600, screen_heigt = 900;


int main()
{
    std::cout << "Mcc up" << std::endl;
    sf::Clock timer;

    sf::RenderWindow window(sf::VideoMode(screen_width, screen_heigt, 32), "OpenGL", sf::Style::Default, sf::ContextSettings(32,8,4,4,0));
    window.setVerticalSyncEnabled(false);

    sf::ContextSettings s = window.getSettings();

    std::cout << "Opengl version: "<< s.majorVersion << "." << s.minorVersion << std::endl;


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        std::cout << "Error: " << glewGetErrorString(err);
    }

    std::cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << std::endl;

    std::cout << "Opengl inited in: " << timer.getElapsedTime().asMilliseconds() << " ms" << std::endl;
    timer.restart();



    engine *game = new engine;
    game->setWindowPointer(&window);
    game->initialize(screen_width,screen_heigt);
    sf::sleep (sf::milliseconds(500));

    std::cout << "Loaded in: " << timer.getElapsedTime().asMilliseconds() << " ms" << std::endl;
    timer.restart();

 /*   glm::vec3 vec1 = glm::vec3(1, 3, 5);
    glm::vec3 vec2 = glm::vec3(2, 2, 10);
    glm::vec3 res = vec1 / vec2;
    std::cout << "GLm test: " << res.x << ", " << res.y << ", " << res.z << std::endl;*/


    bool active = true;
    bool quit = false;
    while (!quit)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Pass evetns to SFGUI
            switch(event.type){
                case sf::Event::Closed:
                    quit = game->quit();
                    break;

                case sf::Event::Resized:
                    game->resize(event.size.width, event.size.height);
                    break;

                case sf::Event::LostFocus:
                    window.setMouseCursorVisible(true);
                    active = false;
                    break;

                case sf::Event::GainedFocus:
                    window.setMouseCursorVisible(false);
                    active = true;
                    break;
                case sf::Event::KeyPressed:
                    if (event.key.code == sf::Keyboard::Escape) quit = game->quit();
                    break;

                default:
                    break;
            }

            game->sfmlEvent(event);
        }

        if(!quit)
        {
            // Update game logic and SFGUI
            if (active) game->process_input();

            int time = timer.getElapsedTime().asMilliseconds();
            timer.restart();
            game->update(time);

            // Render game
            game->render();


            // If game is not active we can save some resourses by sleeping
            if (!active)sf::sleep (sf::milliseconds(50));
        }
    }

    delete game;

    return 0;
}
