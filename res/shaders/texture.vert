
#version 150

in vec4 vertex;
in vec2 texture0;
uniform mat4 matrix;


out vec2 texCoord0;


void main(void){


    texCoord0 = texture0;
    gl_Position = matrix * vertex;
}
