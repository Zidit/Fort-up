#ifndef INPUT_H
#define INPUT_H

#include <list>
#include <string>
#include <map>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <functional>


class action
{
public:
    bool isDown();
    bool isPressed();
    bool changed();

    void setCallBackPressed(std::function<void (void)> func);
    void setCallBackReleased(std::function<void (void)> func);
    void setCallBackDown(std::function<void (void)> func);

    void update(bool isDown);

private:
    bool m_isDown;
    bool m_statusChanged;
    bool m_pressed;
    std::function<void (void)> cbfPressed;
    std::function<void (void)> cbfReleased;
    std::function<void (void)> cbfDown;

};




class inputHandel
{
public:
    inputHandel();

    void update();

    void registerAction(const std::string& function, action* act);

    void registerButton(const std::string& function, sf::Keyboard::Key key);
    void registerButton(const std::string& function, sf::Mouse::Button button);

protected:
private:

    typedef struct _keyboardBinding{
        sf::Keyboard::Key key;
        action *act;
    } keyboardBinding;

    typedef struct _mouseBinding{
        sf::Mouse::Button button;
        action *act;
    } mouseBinding;

    std::list<keyboardBinding> keyboardButtons;
    std::list<mouseBinding> mouseButtons;

    std::map<std::string, action*> actions;

};

extern inputHandel input;

#endif // INPUT_H
