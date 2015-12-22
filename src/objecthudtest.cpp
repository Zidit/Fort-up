#include "objecthudtest.h"
#include "utils.h"


objectHudTest::objectHudTest()
{
    position = glm::vec3(0, 0, 0);
    size = glm::vec3(10,10,0);
}


void objectHudTest::_update(unsigned int dt){

}

void objectHudTest::_render(glm::mat4 *matrix){

    glCheckError(5);
    glBindVertexArray(vao);
    glCheckError(6);

    glActiveTexture( GL_TEXTURE0 );
    texture->bind();


    prog->bind();



    glm::mat4 scale = glm::scale(glm::mat4(), size);
    glm::mat4 move = glm::translate(glm::mat4(), position);
    glm::mat4 temp = *matrix * move * scale ;

    glUniformMatrix4fv(matrixLoc, 1, false, glm::value_ptr(temp));
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glBindVertexArray(0);

    glUseProgram(0);



}

void objectHudTest::init(resourceManager *mgr){


    texture = mgr->loadTexture("test.jpg");
    prog = mgr->loadShader("texture.prg");


    GLuint vertexLoc, texLoc;
    GLuint shader = prog->getHandler();

    vertexLoc = glGetAttribLocation(shader,"vertex");
    matrixLoc = glGetUniformLocation(shader, "matrix");
    texLoc = glGetAttribLocation(shader, "texture0");





    float vertices[] = {0.0f, 0.0f, 0.0f, 1.0f,
                        0.0f, 1.0f, 0.0f, 1.0f,
                        1.0f, 1.0f, 0.0f, 1.0f,
                        1.0f, 1.0f, 0.0f, 1.0f,
                        1.0f, 0.0f, 0.0f, 1.0f,
                        0.0f, 0.0f, 0.0f, 1.0f};

    float text[] = {    0.0f, 0.0f,
                        0.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 1.0f,
                        1.0f, 0.0f,
                        0.0f, 0.0f };


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

     /// bind buffer for text and copy data into buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(text), text, GL_STATIC_DRAW);
    glEnableVertexAttribArray(texLoc);
    glVertexAttribPointer(texLoc, 2, GL_FLOAT, 0, 0, 0);

    glBindVertexArray(0);

}

objectHudTest::~objectHudTest(){
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(2, buffers);
}
