#ifndef ENTITYPLAYER_H
#define ENTITYPLAYER_H

#include "entity.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include "PolyVoxCore/LargeVolume.h"


#include "utils.h"




class entityPlayer : public complexEntity
{
    public:
        entityPlayer();
        virtual ~entityPlayer();

        glm::vec3 getPosition() {return currentPosition;}
        glm::quat getViewQuat() {return pitch * yaw;}
        PolyVox::Vector3DFloat getViewVector();
        PolyVox::Vector3DFloat getEyePosition();

        glm::mat4 getViewMatrix();

        void setPosition(glm::vec3 position) {currentPosition = position;}
        void rotate(float yaw, float pitch);
        void move(glm::vec3 vec);
        void jump();
        void setNoclip(bool noclip);


    protected:
    private:

        glm::quat yaw;
        glm::quat pitch;

        float currentYaw, currentPitch;
};

#endif // ENTITYPLAYER_H
