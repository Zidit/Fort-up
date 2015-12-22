#ifndef OBJECTWORLD_H
#define OBJECTWORLD_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "PolyVoxCore/CubicSurfaceExtractorWithNormals.h"
#include "PolyVoxCore/MarchingCubesSurfaceExtractor.h"
#include "PolyVoxCore/SurfaceMesh.h"
#include "PolyVoxCore/SimpleVolume.h"
#include "gameobject.h"



class objectWorld : public gameObject
{
    public:
        objectWorld();

        void _update(unsigned int dt);
        void _render(glm::mat4 *matrix);
        void init(resourceManager *mgr);
        void destroy(resourceManager *mgr);

    protected:
    private:

        GLuint matrixLoc;
        GLuint vao;
        GLuint m_uBeginIndex, m_uEndIndex;
        GLuint indexBuffer, vertexBuffer;

        resourceShader *prog;
        resourceTexture *top;
        resourceTexture *side;
};

#endif // OBJECTWORLD_H
