#ifndef ENTITY_H
#define ENTITY_H

#include <glm/glm.hpp>

typedef struct {
    glm::vec3 max;
    glm::vec3 min;
}boundingBoxData;


class complexEntity
{
    public:
        void updatePhysics(int dt);

        bool detectCollision(const boundingBoxData &staticObject);
        void solveCollisionX(const boundingBoxData &staticObject);
        void solveCollisionY(const boundingBoxData &staticObject);
        void solveCollisionZ(const boundingBoxData &staticObject);


        glm::vec3 getPosition() {return currentPosition;}
        glm::vec3 getLastPosition() {return lastPosition;}
        void setGrounded(bool grounded) {this->grounded = grounded;}

        complexEntity();
        virtual ~complexEntity();
    protected:
        float mass;
        glm::vec3 lastPosition;
        glm::vec3 currentPosition;

        glm::vec3 acceleration;
        glm::vec3 gravity;
        glm::vec3 velocity;
        glm::vec3 movement;


        boundingBoxData boundingBoxSize;
        bool grounded;
        bool noCollision;

    private:


};



#endif // ENTITY_H
