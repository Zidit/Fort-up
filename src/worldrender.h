#ifndef WORLDRENDER_H
#define WORLDRENDER_H


#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "utils.h"
#include "world.h"
#include "resourcemanager.h"
#include <list>


class worldRenderRegion
{
    public:
        worldRenderRegion(resourceShader *program);
        ~worldRenderRegion();

        void render(const glm::mat4 &projection, const glm::mat4 &view);
        void load(const PolyVox::Vector3DInt32 &position, const PolyVox::SurfaceMesh<PolyVox::PositionMaterial> &mesh);
        void setData(const PolyVox::Region &region, world *world_pointer);
        void load();
        bool getLoaded() {return _loaded;}
        void setRender(bool rend) {_render = rend;}
        bool isRendered() {return _render;}
        PolyVox::Vector3DInt32 getPosition() {return position;}
        PolyVox::Region getRegion() {return region;}

    private:
        GLuint vertexLoc, materialLoc;
        GLuint modelViewMatrixLoc, projectionMatrixLoc, normalMatrixLoc;

        GLuint indexBuffer, vertexBuffer;
        GLuint vao;
        GLuint m_uEndIndex;

        glm::mat4 translate;
        bool _render;
        PolyVox::Vector3DInt32 position;
        PolyVox::Region region;

        bool _loaded;
        world *world_ptr;
        resourceShader *prog;

};


class worldRender
{
    public:
        worldRender();
        ~worldRender();

        bool initialize(resourceManager *mgr, world *world_pointer);
        void render(const glm::mat4 &projection, const glm::mat4 &view);
        void destroy(resourceManager *mgr);
        void loadData(PolyVox::Vector3DInt32 position);


        int blocksRendered;
        int blocksLoaded;


    protected:
    private:
        world *world_ptr;

        resourceShader *prog;
        resourceTexture *top;
        resourceTexture *side;
        resourceTexture *cave;
        GLuint vertexLoc;
        GLuint normalLoc;
        GLuint matrixLoc;

        GLuint texture_array;

        std::vector<worldRenderRegion*> regions;
        std::list<worldRenderRegion*> region_list;


};



#endif // WORLDRENDER_H
