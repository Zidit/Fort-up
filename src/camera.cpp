#include "camera.h"

cameraFPS::cameraFPS()
{
    currentPitch = 0;
    currentYaw = 0;
    currentPosition = glm::vec3(0,0,0);
}


cameraFPS::~cameraFPS()
{

}



glm::mat4 cameraFPS::getViewMatrix()
{

    glm::vec3 up = rotation * glm::vec3(0.0, 1.0, 0.0 );
    glm::vec3 target = rotation * glm::vec3(0.0, 0.0, -1.0) + currentPosition;
    return glm::lookAt(currentPosition, target, up);

}

void cameraFPS::move(glm::vec3 transformation)
{
    currentPosition += rotation * transformation;
}

void cameraFPS::rotate(float yaw, float pitch)
{
    currentPitch += pitch;
    currentYaw += yaw;
    if (currentYaw > glm::half_pi<float>()) currentYaw = glm::half_pi<float>();
    if (currentYaw < -glm::half_pi<float>()) currentYaw = -glm::half_pi<float>();

    rot = glm::angleAxis(currentPitch, glm::vec3(0,1,0)) * glm::angleAxis(currentYaw, glm::vec3(1,0,0));
    rotation = glm::mat3_cast(rot);
}



