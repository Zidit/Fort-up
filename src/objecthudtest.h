#ifndef OBJECTHUDTEST_H
#define OBJECTHUDTEST_H

#include "gameobject.h"

#include <SFML/OpenGL.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class objectHudTest : public gameObject
{
    public:
        objectHudTest();
        ~objectHudTest();

        void _update(unsigned int dt);
        void _render(glm::mat4 *matrix);
        void init(resourceManager *mgr);
        void setPosLeftTop(glm::vec2 pos) {position = glm::vec3(pos, 0);}
        void setPosCenter(glm::vec2 pos) {position = glm::vec3(pos, 0) - size * 0.5f;}
        void setSize(glm::vec2 size) {this->size = glm::vec3(size, 0);}

    protected:

    private:
        GLuint matrixLoc;
        GLuint vao;
        GLuint buffers[2];

    GLuint vertexLoc, texLoc;
        resourceShader *prog;
        resourceTexture *texture;

        glm::vec3 position;
        glm::vec3 size;
};

#endif // OBJECTHUDTEST_H




