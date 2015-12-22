
#include <GL/glew.h>
#include "worldrender.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "resourceHandler.h"

bool listUnique(worldRenderRegion* a, worldRenderRegion* b){

    return a->getRegion() == b->getRegion();

}



worldRender::worldRender()
{
    //ctor
}




worldRender::~worldRender()
{
    for (std::vector<worldRenderRegion*>::iterator it = regions.begin() ; it != regions.end(); ++it)
        delete (*it);
    glDeleteTextures(1, &texture_array);
}

void worldRender::render(const glm::mat4 &projection, const glm::mat4 &view)
{
    blocksRendered = 0;

    prog->bind();


    glActiveTexture( GL_TEXTURE3 );
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array);
    glUniform1i( glGetUniformLocation( prog->getHandler(), "texture3" ), 3 );

    for (auto it = region_list.begin() ; it != region_list.end(); ++it)
    {
        (*it)->render(projection, view);
        if((*it)->isRendered()) blocksRendered++;
    }
    glActiveTexture( GL_TEXTURE0 );
    glUseProgram(0);
}

bool worldRender::initialize(resourceManager *mgr, world *world_pointer)
{
    world_ptr = world_pointer;

    prog = mgr->loadShader("world.prg");

    sf::Image texture;
    texture.create(128, 128 * 8); //if more textures are used, change values also in glTexImage3D function and layer func in frag shader!

    sf::Image img_data;

    if (img_data.loadFromFile("./res/images/grass.jpg"))
        texture.copy(img_data,0 , 128 * 0);
    if (img_data.loadFromFile("./res/images/dirt.jpg"))
        texture.copy(img_data,0,128 * 1);
    if (img_data.loadFromFile("./res/images/stone.jpg"))
        texture.copy(img_data,0,128 * 2);

    glActiveTexture( GL_TEXTURE3 );

    texture.saveToFile("./res/images/save.jpg");
    glEnable(GL_TEXTURE_2D_ARRAY);

    glGenTextures(1, &texture_array);
    glBindTexture(GL_TEXTURE_2D_ARRAY, texture_array);

    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);


    glTexImage3D(
        GL_TEXTURE_2D_ARRAY, 0, GL_RGBA,
        128, 128, 8,
        0,
        GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr()
    );




    glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
    glActiveTexture( GL_TEXTURE0 );

    return true;
}




void worldRender::loadData(PolyVox::Vector3DInt32 position)
{

    //std::cout << "load \n";
    sf::Clock timer;

   // const int32_t blockSize = 32;

    PolyVox::Vector3DInt32 playerPositionBlock = PolyVox::Vector3DInt32(floor(position.getX(), 32), floor(position.getY(), 32), floor(position.getZ(), 32));

    const int _viewDistance = 2;

    PolyVox::Region viewDistance = PolyVox::Region(0,0,0, 31,31,31);
    viewDistance.shiftLowerCorner(PolyVox::Vector3DInt32(-32,-32,-32)*2);
    viewDistance.shiftUpperCorner(PolyVox::Vector3DInt32(32,32,32)*2);

    PolyVox::Region removeDistance = PolyVox::Region(0,0,0, 31,31,31);
    removeDistance.shiftLowerCorner(PolyVox::Vector3DInt32(-32,-32,-32)*20);
    removeDistance.shiftUpperCorner(PolyVox::Vector3DInt32(32,32,32)*20);

    viewDistance.shift(playerPositionBlock);
    removeDistance.shift(playerPositionBlock);

    std::vector<PolyVox::Region> regionsNeeded;

    for (int x = -_viewDistance; x <= _viewDistance; x++)
    {
        for (int z = -_viewDistance; z <= _viewDistance ; z++)
        {
            for(int y = -_viewDistance; y <= _viewDistance; y++)
            {
                PolyVox::Region region = PolyVox::Region(PolyVox::Vector3DInt32(0, 0, 0), PolyVox::Vector3DInt32(31, 31, 31));
                region.shift(PolyVox::Vector3DInt32(x*32, y*32, z*32) + playerPositionBlock );
                regionsNeeded.push_back(region);
            }
        }
    }

    /// TODO: rewrite for one block loading sceme

    for (auto it = region_list.begin(); it != region_list.end(); it++)
    {

        PolyVox::Region region = (*it)->getRegion();

        if(world_ptr->meshNeedUpadte(region)){
            //sf::Clock timer2;
            (*it)->load();
           // std::cout << "Colum mesh loaded in: " << timer2.getElapsedTime().asMilliseconds() << " ms" << std::endl;
        }

        if(regionsOverlap(viewDistance, region))
        {
            (*it)->setRender(true);
        }

        else if (!regionsOverlap(removeDistance, region))
        {
            delete (*it);
            it = region_list.erase(it);
           // std::cout << "Deleted: " << region.getLowerCorner() << "-" << region.getUpperCorner() << std::endl;
        }

        else
        {
            (*it)->setRender(false);
        }

        if(!(*it)->getLoaded()) (*it)->load();

        for(auto it = regionsNeeded.begin(); it != regionsNeeded.end(); it++)
        {
            if(*it == region)
            {
                //std::cout << "List remove  " << it->getLowerCorner() << "-" << it->getUpperCorner() <<  std::endl;
                it = regionsNeeded.erase(it);
                if(it == regionsNeeded.end()) break;
            }
        }

    }

  /*  for(auto it = regionsNeeded.begin(); it != regionsNeeded.end(); it++)
    {
        worldRenderRegion* reg = new worldRenderRegion(prog);
        reg->setData(*it, world_ptr);
        region_list.push_back(reg);
   //     std::cout << "Listed " << it->getLowerCorner() << "-" << it->getUpperCorner() <<  std::endl;
    }*/
    if(regionsNeeded.size())
    {
        worldRenderRegion* reg = new worldRenderRegion(prog);
        reg->setData(regionsNeeded[0], world_ptr);
        region_list.push_back(reg);
   //     std::cout << "Listed " << it->getLowerCorner() << "-" << it->getUpperCorner() <<  std::endl;
    }

   // regionsNeeded.clear();

 //   std::cout << "size: " << region_list.size() << '\n';
    blocksLoaded = region_list.size();
  //  std::cout << "Load function: " << timer.getElapsedTime().asMilliseconds() << " ms  " <<  "size: " << region_list.size() << std::endl;
}







void worldRender::destroy(resourceManager *mgr)
{

}




worldRenderRegion::worldRenderRegion(resourceShader *program) : prog(program)
{
    _render = 1;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &indexBuffer);
    glGenBuffers(1, &vertexBuffer);
}

worldRenderRegion::~worldRenderRegion()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &indexBuffer);
    glDeleteBuffers(1, &vertexBuffer);
}

void worldRenderRegion::render(const glm::mat4 &projection, const glm::mat4 &view){
    if(_render && _loaded)
    {
      // std::cout << "render:" << m_uEndIndex<< " \n";
       // GLuint modelViewMatrixLoc, projectionMatrixLoc, normalMatrixLoc;

        glm::mat4 mv_mat = view * translate;
        glm::mat3 n_mat = glm::transpose(glm::inverse(glm::mat3(mv_mat)));


        glUniformMatrix4fv(normalMatrixLoc, 1, false, glm::value_ptr(n_mat));
        glUniformMatrix4fv(modelViewMatrixLoc, 1, false, glm::value_ptr(mv_mat));
        glUniformMatrix4fv(projectionMatrixLoc, 1, false, glm::value_ptr(projection));

        glCheckError(1);
        glBindVertexArray(vao);
        glCheckError(2);

        glDrawRangeElements(GL_TRIANGLES, 0,m_uEndIndex-1, m_uEndIndex, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);

    }
}
void worldRenderRegion::load()
{

    PolyVox::SurfaceMesh<PolyVox::PositionMaterial> mesh;
    world_ptr->getMesh(region, &mesh);

    const std::vector<uint32_t>& vecIndices = mesh.getIndices();
    const std::vector<PolyVox::PositionMaterial>& vecVertices = mesh.getVertices();

    GLuint shader = prog->getHandler();
    vertexLoc = glGetAttribLocation(shader,"vertex");
    materialLoc = glGetAttribLocation(shader, "material");
    modelViewMatrixLoc = glGetUniformLocation(shader, "mat_mv");
    projectionMatrixLoc = glGetUniformLocation(shader, "mat_p");
    normalMatrixLoc = glGetUniformLocation(shader, "mat_n");

    // std::cout << "load " << vecIndices.size() << " \n";
    ///Generate vao

    glBindVertexArray(vao);

   //Build an OpenGL index buffer

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    const GLvoid* pIndices = static_cast<const GLvoid*>(&(vecIndices[0]));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecIndices.size() * sizeof(uint32_t), pIndices, GL_STATIC_DRAW);

    //Build an OpenGL vertex buffer

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    const GLvoid* pVertices = static_cast<const GLvoid*>(&(vecVertices[0]));
    glBufferData(GL_ARRAY_BUFFER, vecVertices.size() * sizeof(PolyVox::PositionMaterial), pVertices, GL_STATIC_DRAW);

    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, sizeof(PolyVox::PositionMaterial), 0 );
    glEnableVertexAttribArray(materialLoc);
    glVertexAttribPointer(materialLoc, 1, GL_FLOAT, GL_FALSE, sizeof(PolyVox::PositionMaterial),(void*)( 3* sizeof(float)));

    glBindVertexArray(0);

    m_uEndIndex = vecIndices.size();
    _loaded = true;

}

void worldRenderRegion::setData(const PolyVox::Region &region, world *world_pointer)
{

    this->region = region;
    PolyVox::Vector3DInt32 position = region.getLowerCorner();

    glm::vec3 pos = glm::vec3(position.getX(), position.getY(), position.getZ());
    translate = glm::translate(glm::mat4(1), pos);

    world_ptr = world_pointer;

    _loaded = false;

}
