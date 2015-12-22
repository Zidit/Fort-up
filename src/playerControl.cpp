#include "playerControl.h"

playerControl::playerControl(entityPlayer *player)
{
    this->player = player;

    jumpAct.setCallBackDown(std::bind(&entityPlayer::jump, player));
    input.registerAction("jump", &jumpAct);

    moveForward.setCallBackDown(std::bind(&entityPlayer::move, player, glm::vec3(0, 0, -5)));
    input.registerAction("move_forward", &moveForward);

    moveBack.setCallBackDown(std::bind(&entityPlayer::move, player, glm::vec3(0, 0, 5)));
    input.registerAction("move_back", &moveBack);

    moveLeft.setCallBackDown(std::bind(&entityPlayer::move, player, glm::vec3(-5, 0, 0)));
    input.registerAction("move_left", &moveLeft);

    moveRight.setCallBackDown(std::bind(&entityPlayer::move, player, glm::vec3(5, 0, 0)));
    input.registerAction("move_right", &moveRight);


}

playerControl::~playerControl()
{
    //dtor
}
