#include "entityPlayer.h"

entityPlayer::entityPlayer()
{
        mass = 0;
        lastPosition = glm::vec3(0,0,0);
        currentPosition = glm::vec3(0,0,0);
        acceleration = glm::vec3(0,0,0);
        gravity = glm::vec3(0,-9,0);
        velocity = glm::vec3(0,0,0);

        boundingBoxSize = {glm::vec3(0.3, 1.5, 0.3), glm::vec3(-0.3, -0.5, -0.3)};
        grounded = false;
        noCollision = false;
}

entityPlayer::~entityPlayer()
{
    //dtor
}

void entityPlayer::rotate(float yaw, float pitch)
{
    currentPitch += pitch;
    currentYaw += yaw;
    if (currentYaw > glm::half_pi<float>()) currentYaw = glm::half_pi<float>();
    if (currentYaw < -glm::half_pi<float>()) currentYaw = -glm::half_pi<float>();

    this->pitch = glm::angleAxis(currentPitch, glm::vec3(0,1,0));
    this->yaw = glm::angleAxis(currentYaw, glm::vec3(1,0,0));
}

void entityPlayer::jump()
{
    if (grounded)
        velocity = glm::vec3(0,10,0);
}

void entityPlayer::move(glm::vec3 vec)
{
    glm::mat3 rotation;

    if (noCollision)
    {
        rotation = glm::mat3_cast(pitch * yaw);
        movement = rotation * (vec * 5.0f);
    }
    else
    {
        vec.y = 0;
        rotation = glm::mat3_cast(pitch);
        movement = rotation * vec ;
    }
}

void entityPlayer::setNoclip(bool noclip)
{
    noCollision = noclip;
    if(noclip) gravity = glm::vec3(0,0,0);
    else gravity = glm::vec3(0,-9.8,0);
    velocity = glm::vec3(0,0,0);
}

glm::mat4 entityPlayer::getViewMatrix()
{
    glm::vec3 cameraPosition = currentPosition + glm::vec3(0, 1, 0);
    glm::mat3 rotation = glm::mat3_cast(pitch * yaw);
    glm::vec3 up = rotation * glm::vec3(0.0, 1.0, 0.0 );
    glm::vec3 target = rotation * glm::vec3(0.0, 0.0, -1.0) + cameraPosition;
    return glm::lookAt(cameraPosition, target, up);
}

PolyVox::Vector3DFloat entityPlayer::getViewVector()
{
    glm::vec3 target = glm::mat3_cast(pitch * yaw) * glm::vec3(0.0, 0.0, -1.0);
    PolyVox::Vector3DFloat direction = castTo3DFloat(target);
    direction.normalise();
    return direction;
}

PolyVox::Vector3DFloat entityPlayer::getEyePosition()
{
    glm::vec3 cameraPosition = currentPosition + glm::vec3(0, 1, 0);
    return castTo3DFloat(cameraPosition);
}
