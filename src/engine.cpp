#include "engine.h"
#include "PolyVoxCore/Raycast.h"
#include "utils.h"
#include <sstream>
#include "collisions.h"

engine::engine()
{
    end_game = 0;
}

engine::~engine()
{

}


bool engine::initialize(int width, int height){

//    std::cout << "Do init " << std::endl;
    window_ptr->setActive();
    resize(width, height);


    /*objectHudTest* item = new objectHudTest;
    item->setPosCenter(glm::vec2(width/2, height/2));

    addHudObject(item);*/


    srand(41);
    gameWorld.initialize();
    gameWorldRender.initialize(&resourceMgr, &gameWorld);

    player0.setPosition(glm::vec3(1, 50.4, 1));
    player0Control = new playerControl(&player0);

    debug.initialize(&desktop);
    toolBar.initialize(&desktop);

    gameWorldRender.loadData(roundVectorTo3DInt(castTo3DFloat(player0.getPosition())));
    freeMouse = false;

    input.registerButton("move_forward",sf::Keyboard::W);
    input.registerButton("move_back",sf::Keyboard::S);
    input.registerButton("move_right",sf::Keyboard::D);
    input.registerButton("move_left",sf::Keyboard::A);
    input.registerButton("jump", sf::Keyboard::Space);

    input.registerAction("releaseMouse", &fm);
    input.registerButton("releaseMouse", sf::Keyboard::G);

    input.registerAction("hit", &hit);
    input.registerAction("use", &use);
    input.registerButton("hit", sf::Mouse::Button::Left);
    input.registerButton("use", sf::Mouse::Button::Right);


    gui = guiHandlerPtr(new guiHandler);

    guiObjectPtr test(new guiImage("test.jpg"));
    gui->addChild(test);

    sf::Transform m;
    m.translate(300,200);
    m.scale(0.2, 0.2);
    test->setParentTransformation(m);

    return true;


}

void engine::resize(int width, int height){

    perspective = glm::perspective(45.0f, (float)width/(float)height, 0.1f, 1000.f);
    ortho = glm::ortho(0.0f, (float)width, (float)height, 0.0f);
    glViewport(0, 0, width, height);

}

void engine::process_input(){
    if(end_game) return;

  //  std::cout << "Do input: ";
    input.update();


    sf::Vector2i center = sf::Vector2i(window_ptr->getSize().x / 2 ,window_ptr->getSize().y / 2);
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*window_ptr);
    sf::Vector2i mouseDelta = center - mousePosition;

    debug.setCursor(mousePosition.x, mousePosition.y);

    if(!freeMouse) {
        player0.rotate((float)mouseDelta.y/300, (float)mouseDelta.x/300);
        sf::Mouse::setPosition(center, *window_ptr);
        window_ptr->setMouseCursorVisible(false);
    } else {
        window_ptr->setMouseCursorVisible(true);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) resourceMgr.reloadShader("world.prg");
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::U)) player0.setNoclip(true);
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::I)) player0.setNoclip(false);


    if(fm.isPressed())
        freeMouse ? freeMouse = false : freeMouse = true;

    if(hit.isPressed() && !freeMouse)
    {
        PolyVox::Vector3DInt32 result;
        if(gameWorld.raycast(player0.getEyePosition(), player0.getViewVector() *= 10, result))
        {
            gameWorld.hitBlock(result);
        }
    }

    if(use.isPressed() && !freeMouse){
        PolyVox::Vector3DInt32 hit;
        PolyVox::Vector3DInt32 lastMiss;
        if(gameWorld.raycast(player0.getEyePosition(), player0.getViewVector() *= 10, hit, lastMiss))
        {
            if(!gameWorld.useBlock(hit))
            {
                gameWorld.placeBlock(lastMiss, 1);
            }
        }
    }

 //   std::cout << " done" << std::endl;
    return;
}

void engine::update(int dt){
    if(end_game)
        return;

  //  std::cout << "Do update: ";

    player0.updatePhysics(dt);
    collisionWithWorld(player0, gameWorld);


   // testO->setPos(glm::vec3(0,0,0));
    for (std::vector<gameObject*> ::iterator it = gameObjects.begin() ; it != gameObjects.end(); ++it)
    {
        (*it)->update(dt);
    }

 //   std::cout << ".";

    debug.setPlayerPosition(player0.getPosition());

    PolyVox::Vector3DInt32 result;
    if(gameWorld.raycast(player0.getEyePosition(), player0.getViewVector() *= 10, result))
    {
        block b = gameWorld.getBlock(result);
        debug.setPlayerTarget(castToVec3(b.getPosition()), b.getType(), b.getValue());
    }
    else
        debug.setPlayerTarget(glm::vec3(0,0,0),0,0);
    debug.setRenderData(gameWorldRender.blocksRendered, gameWorldRender.blocksLoaded);

  //  std::cout << ".";
/*
    static int frames = 0;
    frames++;
    static int time = 0;
    time += dt;
    if(time > 250){
        float fps = (float)frames / (float)time / 1000.0 * 4.0;
        debug.setFps((int)fps);
        time -= 250;
        frames = 0;

    }

    std::cout << ".";*/


    desktop.Update((float)dt / 1000.0);



   // std::cout << " done " << std::endl;

}

void engine::render(){
    if(end_game) return;

  //  std::cout << "Do render: ";

    window_ptr->setActive();

    glClearColor (0.0f, 0.0f, 0.2f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ///Render 3D
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    glm::mat4 matrix = perspective * player0.getViewMatrix();
    for (auto it = gameObjects.begin() ; it != gameObjects.end(); ++it)
        (*it)->render(&matrix);


    gameWorldRender.loadData(roundVectorTo3DInt(castTo3DFloat(player0.getPosition())));
    gameWorldRender.render(perspective, player0.getViewMatrix());
    gameWorld.tick();


  ///Render hud
    glDisable(GL_DEPTH_TEST);

    for (auto ith = hudObjects.begin() ; ith != hudObjects.end(); ++ith)
        (*ith)->render(&ortho);



    window_ptr->pushGLStates();
   // window_ptr->draw(text);
   // window_ptr->resetGLStates();
    sfgui.Display( *window_ptr );

    gui->render(*window_ptr);
//
    window_ptr->popGLStates();
//
    window_ptr->display();

 //   std::cout << "done " << std::endl;


}

void engine::sfmlEvent(sf::Event event){
    desktop.HandleEvent( event );
}


void engine::error(std::string error){

    std::cout << "E: " << error << std::endl;

}

void engine::warning(std::string error){

    std::cout << "W: " << error << std::endl;

}

bool engine::quit(){

   // resourceMgr.releaseAll();
    gameWorld.save();
    end_game = 1;
    return true;

}

void engine::addGameObject(gameObject *object)
{
    object->init(&resourceMgr);
    gameObjects.push_back(object);
}

void engine::addHudObject(gameObject *object)
{
    object->init(&resourceMgr);
    hudObjects.push_back(object);
}

