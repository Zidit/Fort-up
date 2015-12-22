#ifndef TESTOBJECT_H
#define TESTOBJECT_H

#include "gameobject.h"

#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class testObject : public gameObject
{
    public:
        testObject();
        virtual ~testObject();

        void _update(unsigned int dt);
        void _render(glm::mat4 *matrix);
        void init(resourceManager *mgr);
        void destroy(resourceManager *mgr);
        void setPos(glm::vec3 poss) {pos = poss;}

    protected:
    private:
        glm::vec3 pos;
        float theta;
    GLuint vertexLoc, colorLoc;
        GLuint matrixLoc;
        GLuint vao;
        resourceShader *prog;

};

class objectFloor : public gameObject
{
    public:
        objectFloor();
        virtual ~objectFloor();

        void _update(unsigned int dt){;}
        void _render(glm::mat4 *matrix);
        void init(resourceManager *mgr);
        void destroy(resourceManager *mgr);

    protected:
    private:
        GLuint vao;
        GLuint matrixLoc;

        resourceTexture *texture;
        resourceShader *prog;

};

#endif // TESTOBJECT_H
