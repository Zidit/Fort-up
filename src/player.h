#ifndef PLAYER_H
#define PLAYER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/constants.hpp>
#include "PolyVoxCore/LargeVolume.h"
#include "PolyVoxCore/Raycast.h"
#include "world.h"
#include "utils.h"
#include "input.h"

class player
{
    public:
        player();
        virtual ~player();

        void update(int dt);
        void setSampler(PolyVox::LargeVolume<rawBlockData>::Sampler *smp) {sampler = smp;}


        glm::vec3 getPosition() {return currentPosition;}
        glm::quat getViewQuat() {return pitch * yaw;}
        PolyVox::Vector3DFloat getViewVector();
        PolyVox::Vector3DFloat getEyePosition();

        glm::mat4 getViewMatrix();

        void setPosition(glm::vec3 position) {currentPosition = position;}
        void rotate(float yaw, float pitch);
        void move(glm::vec3 vec);
        void jump();
        void setNoclip(bool noclip) {_noclip = noclip;}



    protected:
    private:
        glm::vec3 currentPosition;
        glm::vec3 acceleration;
        glm::vec3 velocity;
        glm::vec3 controller_movement;

        glm::quat yaw;
        glm::quat pitch;

        PolyVox::LargeVolume<rawBlockData>::Sampler *sampler;
        PolyVox::LargeVolume<rawBlockData> *world;
        bool onGround;
        bool _noclip;
        float currentYaw, currentPitch;

        action jumpAct;
        action moveForward;
        action moveBack;
        action moveLeft;
        action moveRight;



};




#endif // PLAYER_H
