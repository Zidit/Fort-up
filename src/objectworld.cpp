#include "objectworld.h"
#include <iostream>
#include <GL/glew.h>
#include <stdlib.h>

objectWorld::objectWorld()
{
    //ctor
}

using namespace PolyVox;

void objectWorld::_update(unsigned int dt){

}

void objectWorld::_render(glm::mat4 *matrix){


//    glm::mat4 rot = glm::rotate(glm::mat4(), theta, glm::vec3(0.0f, 0.0f, 1.0f));
   // glm::mat4 trans = glm::translate(glm::mat4(1.0f), pos);
//     glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1, 1, 1));

//    glm::mat4 temp = *matrix * scale;


    prog->bind();

    glActiveTexture( GL_TEXTURE0 );
    top->bind();
    glUniform1i( glGetUniformLocation( prog->getHandler(), "texture0" ), 0 );

    glActiveTexture( GL_TEXTURE1 );
    side->bind();
    glUniform1i( glGetUniformLocation( prog->getHandler(), "texture1" ), 1 );




    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(*matrix));
    glBindVertexArray(vao);


    glDrawRangeElements(GL_TRIANGLES, m_uBeginIndex, m_uEndIndex-1, m_uEndIndex - m_uBeginIndex, GL_UNSIGNED_INT, 0);


    glBindVertexArray(0);
    glUseProgram(0);


}

void objectWorld::init(resourceManager *mgr){

    SimpleVolume<uint8_t> volData(PolyVox::Region(Vector3DInt32(0,0,0), Vector3DInt32(15, 3, 15)));
    //This vector hold the position of the center of the volume
    Vector3DFloat v3dVolCenter(volData.getWidth() / 2, volData.getHeight() / 2, volData.getDepth() / 2);

    //This three-level for loop iterates over every voxel in the volume
    for (int z = 0; z < volData.getDepth(); z++)
    {
        for (int x = 0; x < volData.getWidth(); x++)
        {
            int k = rand() % 3;
            for (int y = 0; y < volData.getHeight(); y++)
            {

                            //Store our current position as a vector...
                            //Vector3DFloat v3dCurrentPos(x,y,z);
                            //And compute how far the current position is from the center of the volume
                            //float fDistToCenter = (v3dCurrentPos - v3dVolCenter).length();

                            uint8_t uVoxelValue = 255;

                            //If the current voxel is less than 'radius' units from the center then we make it solid.
                            if(y > k)
                            {
                                    //Our new voxel value
                                    uVoxelValue = 0;
                            }

                            //Wrte the voxel value into the volume
                            volData.setVoxelAt(x, y, z, uVoxelValue);
                    }
            }
    }


    SurfaceMesh<PositionMaterialNormal> mesh;
    CubicSurfaceExtractorWithNormals< SimpleVolume<uint8_t> > surfaceExtractor(&volData, volData.getEnclosingRegion(), &mesh);

    surfaceExtractor.execute();

    const std::vector<uint32_t>& vecIndices = mesh.getIndices();
    const std::vector<PositionMaterialNormal>& vecVertices = mesh.getVertices();

    prog = mgr->loadShader("world.prg");
    GLuint shader = prog->getHandler();

    glActiveTexture( GL_TEXTURE0 );
    top = mgr->loadTexture("grass.jpg");
    glActiveTexture( GL_TEXTURE1 );
    side = mgr->loadTexture("dirt.jpg");


    GLuint vertexLoc = glGetAttribLocation(shader,"vertex");
    GLuint normalLoc = glGetAttribLocation(shader, "normal");
    matrixLoc = glGetUniformLocation(shader, "matrix");


    ///Generate vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

   //Build an OpenGL index buffer
    glGenBuffers(1, &indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
    const GLvoid* pIndices = static_cast<const GLvoid*>(&(vecIndices[0]));
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, vecIndices.size() * sizeof(uint32_t), pIndices, GL_STATIC_DRAW);

    //Build an OpenGL vertex buffer
    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    const GLvoid* pVertices = static_cast<const GLvoid*>(&(vecVertices[0]));
    glBufferData(GL_ARRAY_BUFFER, vecVertices.size() * sizeof(PositionMaterialNormal), pVertices, GL_STATIC_DRAW);


    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, sizeof(PositionMaterialNormal), 0 );
    glEnableVertexAttribArray(normalLoc);
    glVertexAttribPointer(normalLoc, 3, GL_FLOAT, GL_FALSE, sizeof(PositionMaterialNormal),(void*)( 3*sizeof(float)));

    glBindVertexArray(0);
    m_uBeginIndex = 0;
    m_uEndIndex = vecIndices.size();



}

void objectWorld::destroy(resourceManager *mgr){
    glDeleteVertexArrays(1, &vao);

}



