#include "collisions.h"
#include "utils.h"
#include <iostream>


bool solveCollisionY(glm::vec3 pos, complexEntity &entity, world &staicWorld)
{
    boundingBoxData bb;
    if(staicWorld.getBoundingBox(castTo3DInt(entity.getLastPosition() + pos) , bb))
    {
        if(entity.detectCollision(bb)){
            entity.solveCollisionY(bb);
            return true;
        }
    }
    return false;
}

bool solveCollisionX(glm::vec3 pos, complexEntity &entity, world &staicWorld)
{
    boundingBoxData bb;
    if(staicWorld.getBoundingBox(castTo3DInt(entity.getLastPosition() + pos) , bb))
    {
        if(entity.detectCollision(bb)){
            entity.solveCollisionX(bb);
            return true;
        }
    }
    return false;
}

bool solveCollisionZ(glm::vec3 pos, complexEntity &entity, world &staicWorld)
{
    boundingBoxData bb;
    if(staicWorld.getBoundingBox(castTo3DInt(entity.getLastPosition() + pos) , bb))
    {
        if(entity.detectCollision(bb)){
            entity.solveCollisionZ(bb);
            return true;
        }
    }
    return false;
}



void collisionWithWorld(complexEntity &entity, world &staicWorld)
{

    // detect collisin with ground

    if(solveCollisionY(glm::vec3(0,-1,0), entity, staicWorld))
        entity.setGrounded(true);
    solveCollisionY(glm::vec3(0,2,0), entity, staicWorld);


    for(int y =  0; y <= 1; y++){
        solveCollisionX(glm::vec3(1,y,0), entity, staicWorld);
        solveCollisionX(glm::vec3(-1,y,0), entity, staicWorld);
        solveCollisionZ(glm::vec3(0,y,1), entity, staicWorld);
        solveCollisionZ(glm::vec3(0,y,-1), entity, staicWorld);

        solveCollisionX(glm::vec3(1,y,1), entity, staicWorld);
        solveCollisionX(glm::vec3(-1,y,1), entity, staicWorld);
        solveCollisionX(glm::vec3(1,y,-1), entity, staicWorld);
        solveCollisionX(glm::vec3(-1,y,-1), entity, staicWorld);

        solveCollisionZ(glm::vec3(1,y,1), entity, staicWorld);
        solveCollisionZ(glm::vec3(1,y,-1), entity, staicWorld);
        solveCollisionZ(glm::vec3(-1,y,1), entity, staicWorld);
        solveCollisionZ(glm::vec3(-1,y,-1), entity, staicWorld);
    }

    for(int x = -1; x <= 1; x++){
    for(int z = -1; z <= 1; z++){
        if(solveCollisionY(glm::vec3(x,-1,z), entity, staicWorld))
            entity.setGrounded(true);
        solveCollisionY(glm::vec3(x,2,z), entity, staicWorld);
    }}


}

