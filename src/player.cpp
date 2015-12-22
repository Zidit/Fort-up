#include "player.h"


player::player()
{
    onGround = true;
    currentPitch = 0;
    currentYaw = 0;
    currentPosition = glm::vec3(0,5,0);
    sampler = NULL;
    _noclip = false;

    jumpAct.setCallBackDown(std::bind(&player::jump, this));
    input.registerAction("jump", &jumpAct);

    moveForward.setCallBackDown(std::bind(&player::move, this, glm::vec3(0, 0, -10)));
    input.registerAction("move_forward", &moveForward);

    moveBack.setCallBackDown(std::bind(&player::move, this, glm::vec3(0, 0, 10)));
    input.registerAction("move_back", &moveBack);

    moveLeft.setCallBackDown(std::bind(&player::move, this, glm::vec3(-10, 0, 0)));
    input.registerAction("move_left", &moveLeft);

    moveRight.setCallBackDown(std::bind(&player::move, this, glm::vec3(10, 0, 0)));
    input.registerAction("move_right", &moveRight);



}

player::~player()
{
    delete sampler;
}

void player::update(int dt)
{
    if (_noclip)
    {
        currentPosition += controller_movement * ((float)dt / 1000);
        controller_movement = glm::vec3(0,0,0);
        velocity = glm::vec3(0,0,0);
        return;
    }

    glm::vec3 moveLimitMax = glm::vec3(0.999, 0.999, 0.999);
    glm::vec3 moveLimitMin = glm::vec3(-0.999, -0.999, -0.999);
    onGround = false;

    PolyVox::Vector3DFloat pos = castTo3DFloat(currentPosition);

    //std::cout << pos << std::endl;
    sampler->setPosition(roundVectorTo3DInt(pos));

    ///Calculate speed and movement
    velocity += acceleration * ((float)dt / 1000 );
    glm::vec3 movement = velocity * ((float)dt / 1000);

    movement += controller_movement * ((float)dt / 1000);
    controller_movement = glm::vec3(0,0,0);


    ///Dont fall through ground
    if(sampler->peekVoxel0px1ny0pz()) moveLimitMin.y = -(currentPosition.y - floor(currentPosition.y) - 0.002);


    ///Collisino detection of walls
    if(sampler->peekVoxel1nx0py0pz() || sampler->peekVoxel1nx1py0pz()) moveLimitMin.x = -(0.5 + (currentPosition.x - floor(currentPosition.x + 0.5)))+ 0.3;
    if(sampler->peekVoxel1px0py0pz() || sampler->peekVoxel1px1py0pz()) moveLimitMax.x =   0.5 - (currentPosition.x - floor(currentPosition.x + 0.5)) - 0.3;
    if(sampler->peekVoxel0px0py1nz() || sampler->peekVoxel0px1py1nz()) moveLimitMin.z = -(0.5 + (currentPosition.z - floor(currentPosition.z + 0.5)))+ 0.3;
    if(sampler->peekVoxel0px0py1pz() || sampler->peekVoxel0px1py1pz()) moveLimitMax.z =   0.5 - (currentPosition.z - floor(currentPosition.z + 0.5)) - 0.3;

    ///See if player hits head on ceiling
    sampler->movePositiveY();
    if (sampler->peekVoxel0px1py0pz())
    {
        moveLimitMax.y = 0.5 - (currentPosition.y - floor(currentPosition.y + 0.5)) - 0.3;
        if(velocity.y > 0) velocity.y = 0;
    }
    currentPosition += glm::clamp(movement, moveLimitMin, moveLimitMax);


    sampler->moveNegativeY();
    if(sampler->peekVoxel0px1ny0pz() && (currentPosition.y - floor(currentPosition.y)) < 0.01 ) onGround = true;


    if (onGround)
    {
        velocity = glm::vec3(0,0,0);
        acceleration = glm::vec3(0,0,0);
    }
    else
    {
        acceleration = glm::vec3(0,-9.8,0);
    }



}

void player::rotate(float yaw, float pitch)
{
    currentPitch += pitch;
    currentYaw += yaw;
    if (currentYaw > glm::half_pi<float>()) currentYaw = glm::half_pi<float>();
    if (currentYaw < -glm::half_pi<float>()) currentYaw = -glm::half_pi<float>();

    this->pitch = glm::angleAxis(currentPitch, glm::vec3(0,1,0));
    this->yaw = glm::angleAxis(currentYaw, glm::vec3(1,0,0));
}

void player::jump()
{
    if (onGround)
        velocity = glm::vec3(0,15,0);
    onGround = false;

}

void player::move(glm::vec3 vec)
{
    glm::mat3 rotation;

    if (_noclip)
    {
        rotation = glm::mat3_cast(pitch * yaw);
        controller_movement = rotation * (vec * 5.0f);
    }
    else
    {
        vec.y = 0;
        rotation = glm::mat3_cast(pitch);
        controller_movement = rotation * vec ;
    }
}

glm::mat4 player::getViewMatrix()
{
    glm::vec3 cameraPosition = currentPosition + glm::vec3(0, 1, 0);
    glm::mat3 rotation = glm::mat3_cast(pitch * yaw);
    glm::vec3 up = rotation * glm::vec3(0.0, 1.0, 0.0 );
    glm::vec3 target = rotation * glm::vec3(0.0, 0.0, -1.0) + cameraPosition;
    return glm::lookAt(cameraPosition, target, up);
}

PolyVox::Vector3DFloat player::getViewVector()
{
    glm::vec3 target = glm::mat3_cast(pitch * yaw) * glm::vec3(0.0, 0.0, -1.0);
    PolyVox::Vector3DFloat direction = castTo3DFloat(target);
    direction.normalise();
    return direction;
}

PolyVox::Vector3DFloat player::getEyePosition()
{
    glm::vec3 cameraPosition = currentPosition + glm::vec3(0, 1, 0);
    return castTo3DFloat(cameraPosition);
}






