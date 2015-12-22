#include "testobject.h"
#include <glm/gtc/random.hpp>
#include <stdlib.h>
#include <glm/gtc/constants.hpp>
testObject::testObject()
{
    //ctor
}

testObject::~testObject()
{
    //dtor
}



void testObject::_update(unsigned int dt){
  //  pos += glm::vec3(glm::linearRand(glm::vec2(-0.01), glm::vec2(0.01)), 0) ;
   // theta += (float)dt/100 * (rand() % 10);
}

void testObject::_render(glm::mat4 *matrix){


  //  glm::mat4 rot = glm::rotate(glm::mat4(), theta, glm::vec3(0.0f, 0.0f, 1.0f));
    glm::mat4 trans = glm::translate(glm::mat4(), pos);

    glm::mat4 temp = *matrix  * trans;

    prog->bind();
    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(temp));
    glBindVertexArray(vao);

    //glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    glDrawArrays(GL_LINES, 0, 2);
    //glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    glBindVertexArray(0);
    glUseProgram(0);
    glDisableVertexAttribArray(vertexLoc);
    glDisableVertexAttribArray(colorLoc);

}

void testObject::init(resourceManager *mgr){
    theta = 0;


    prog = mgr->loadShader("basic.prg");


    GLuint shader = prog->getHandler();

    vertexLoc = glGetAttribLocation(shader,"vertex");
    colorLoc = glGetAttribLocation(shader, "color");
    matrixLoc = glGetUniformLocation(shader, "matrix");

    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f,
                        0.0f, 20.0f, 0.0f, 1.0f,
                        0.0f, 2.0f, -5.0f, 1.0f};

    float colors[] = {  1.0f, 0.0f, 0.0f, 1.0f,
                        0.5f, 0.0f, 1.0f, 1.0f,
                        1.0f, 0.2f, 0.0f, 1.0f};




    ///Generate vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /// Generate two slots for the vertex and color buffers
    GLuint buffers[2];
    glGenBuffers(2, buffers);

    /// bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

    /// bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);


    glBindVertexArray(0);


}

void testObject::destroy(resourceManager *mgr){
    glDeleteVertexArrays(1, &vao);

}






objectFloor::objectFloor()
{
    //ctor
}

objectFloor::~objectFloor()
{
    //dtor
}




void objectFloor::_render(glm::mat4 *matrix){

    glActiveTexture( GL_TEXTURE0 );
    texture->bind();

    prog->bind();
    glBindVertexArray(vao);

    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(*matrix));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::half_pi<float>(), glm::vec3(1.0, 0.0, 0.0) );
    glm::mat4 temp = *matrix * rot;
    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(temp));
    glDrawArrays(GL_TRIANGLES, 0, 6);


    rot = glm::rotate(glm::mat4(1.0), glm::half_pi<float>(), glm::vec3(0.0, 0.0, 1.0) );
    temp = *matrix * rot;
    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(temp));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);
    glUseProgram(0);


}

void objectFloor::init(resourceManager *mgr){

    texture = mgr->loadTexture("test.jpg");
    prog = mgr->loadShader("texture.prg");




    GLuint vertexLoc, colorLoc, texLoc;
    GLuint shader = prog->getHandler();

    vertexLoc = glGetAttribLocation(shader,"vertex");
    colorLoc = glGetAttribLocation(shader, "color");
    matrixLoc = glGetUniformLocation(shader, "matrix");
    texLoc = glGetAttribLocation(shader, "texture0");

    float vertices[] = {10.0f,  0.0f, 10.0f,  1.0f,
                        10.0f,  0.0f, -10.0f, 1.0f,
                        -10.0f, 0.0f, -10.0f, 1.0f,
                        -10.0f, 0.0f, -10.0f, 1.0f,
                        -10.0f, 0.0f, 10.0f,  1.0f,
                        10.0f,  0.0f, 10.0f,  1.0f};

    float colors[] = {  0.3f, 0.5f, 0.2f, 1.0f,
                        0.3f, 0.5f, 0.2f, 1.0f,
                        0.3f, 0.5f, 0.2f, 1.0f,
                        0.3f, 0.5f, 0.2f, 1.0f,
                        0.3f, 0.5f, 0.2f, 1.0f,
                        0.3f, 0.5f, 0.2f, 1.0f};

    float text[] = {    0.0f, 0.0f,
                        1.0f, 0.0f,
                        1.0f, 1.0f,
                        1.0f, 1.0f,
                        0.0f, 1.0f,
                        0.0f, 0.0f };


    ///Generate vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    /// Generate two slots for the vertex and color buffers
    GLuint buffers[3];
    glGenBuffers(3, buffers);

    /// bind buffer for vertices and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(vertexLoc);
    glVertexAttribPointer(vertexLoc, 4, GL_FLOAT, 0, 0, 0);

    /// bind buffer for colors and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glEnableVertexAttribArray(colorLoc);
    glVertexAttribPointer(colorLoc, 4, GL_FLOAT, 0, 0, 0);

     /// bind buffer for text and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text), text, GL_STATIC_DRAW);
    glEnableVertexAttribArray(texLoc);
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, 0, 0, 0);

    glBindVertexArray(0);




}

void objectFloor::destroy(resourceManager *mgr){
    glDeleteVertexArrays(1, &vao);

}
