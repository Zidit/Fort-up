#include "entity.h"
#include <iostream>
complexEntity::complexEntity()
{
    //ctor
}

complexEntity::~complexEntity()
{
    //dtor
}

void complexEntity::updatePhysics(int dt)
{
    float time = (float)dt / 1000.0f;

    lastPosition = currentPosition;

    velocity += acceleration * time;
    if(!grounded) velocity += gravity * time;

    currentPosition += (velocity + movement)* time;
    movement = glm::vec3(0,0,0);

    grounded = false;

}



bool complexEntity::detectCollision(const boundingBoxData &staticObject)
{
    if(noCollision) return false;
    boundingBoxData boundingBox;
    boundingBox.max = boundingBoxSize.max + currentPosition;
    boundingBox.min = boundingBoxSize.min + currentPosition;

    if(boundingBox.max.x <= staticObject.min.x) return false;
    if(boundingBox.min.x >= staticObject.max.x) return false;

    if(boundingBox.max.y <= staticObject.min.y) return false;
    if(boundingBox.min.y >= staticObject.max.y) return false;

    if(boundingBox.max.z <= staticObject.min.z) return false;
    if(boundingBox.min.z >= staticObject.max.z) return false;

    return true;
}



void complexEntity::solveCollisionX(const boundingBoxData &staticObject)
{
    float overlapMax = glm::min(staticObject.max.x, boundingBoxSize.max.x + currentPosition.x);
    float overlapMin = glm::max(staticObject.min.x, boundingBoxSize.min.x + currentPosition.x);

    glm::vec3 overlap = glm::vec3(overlapMax - overlapMin,0,0);

    if (staticObject.max.x < boundingBoxSize.max.x + currentPosition.x)
        currentPosition = currentPosition + overlap;
    else
        currentPosition = currentPosition - overlap;

    velocity.x = 0;
    acceleration.x = 0;
}

void complexEntity::solveCollisionY(const boundingBoxData &staticObject)
{
    float overlapMax = glm::min(staticObject.max.y, boundingBoxSize.max.y + currentPosition.y);
    float overlapMin = glm::max(staticObject.min.y, boundingBoxSize.min.y + currentPosition.y);

    glm::vec3 overlap = glm::vec3(0,overlapMax - overlapMin,0);

    if (staticObject.max.y < boundingBoxSize.max.y + currentPosition.y)
        currentPosition = currentPosition + overlap;
    else
        currentPosition = currentPosition - overlap;

    velocity.y = 0;
    acceleration.y = 0;

}

void complexEntity::solveCollisionZ(const boundingBoxData &staticObject)
{
    float overlapMax = glm::min(staticObject.max.z, boundingBoxSize.max.z + currentPosition.z);
    float overlapMin = glm::max(staticObject.min.z, boundingBoxSize.min.z + currentPosition.z);

    glm::vec3 overlap = glm::vec3(0,0,overlapMax - overlapMin);

    if (staticObject.max.z < boundingBoxSize.max.z + currentPosition.z)
        currentPosition = currentPosition + overlap;
    else
        currentPosition = currentPosition - overlap;

    velocity.z = 0;
    acceleration.z = 0;
}

