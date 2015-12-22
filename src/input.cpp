#include "input.h"




bool action::isDown()
{
    return m_isDown;
}

bool action::changed()
{
    return m_statusChanged;
}

bool action::isPressed()
{
    return m_pressed;
}

void action::setCallBackPressed(std::function<void (void)> func)
{
    cbfPressed = func;
}
void action::setCallBackReleased(std::function<void (void)> func)
{
    cbfReleased = func;
}

void action::setCallBackDown(std::function<void (void)> func)
{
    cbfDown = func;
}

void action::update(bool isDown)
{
    m_statusChanged = false;
    m_pressed = false;

    if (isDown){
        if(!m_isDown){
            m_statusChanged = true;
            m_pressed = true;
            if(cbfPressed) cbfPressed();
        }
        else {
            if(cbfDown) cbfDown();
        }
    }

    if(!isDown && m_isDown){
        m_statusChanged = true;
        if(cbfReleased) cbfReleased();
    }

    m_isDown = isDown;
}




void inputHandel::update()
{

    for (auto it : keyboardButtons){
        it.act->update(sf::Keyboard::isKeyPressed(it.key));
    }

    for (auto it : mouseButtons){
        it.act->update(sf::Mouse::isButtonPressed(it.button));
    }


}

void inputHandel::registerAction(const std::string& name, action* act)
{
    auto it = actions.find(name);
    if ( it != actions.end() )
        return;

    actions.insert( std::make_pair( name, act) );

}

void inputHandel::registerButton(const std::string& name, sf::Keyboard::Key key)
{
    auto it = actions.find(name);
    if ( it != actions.end() ) {
        keyboardBinding keyBind;
        keyBind.key = key;
        keyBind.act = it->second;

        keyboardButtons.push_back(keyBind);

    }



}

void inputHandel::registerButton(const std::string& name, sf::Mouse::Button button)
{
    auto it = actions.find(name);
    if ( it != actions.end() ) {
        mouseBinding keyBind;
        keyBind.button = button;
        keyBind.act = it->second;

        mouseButtons.push_back(keyBind);

    }
}





inputHandel::inputHandel()
{
    //ctor
}

inputHandel input;
