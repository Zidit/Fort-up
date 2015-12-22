#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>

class cameraFPS
{
    public:
        cameraFPS();
        virtual ~cameraFPS();

        glm::mat4 getViewMatrix();

        void move(glm::vec3 transformation);
        void rotate(float yaw, float pitch);
        void setPosition(glm::vec3 pos) {currentPosition = pos;}


    protected:
    private:
        glm::vec3 currentPosition;
        glm::mat3 rotation;
        glm::quat rot;
        float currentYaw, currentPitch;
};

#endif // CAMERA_H
