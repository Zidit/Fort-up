
#version 150

in vec4 vertex;
in float material;

uniform mat4 mat_mv;
uniform mat4 mat_p;
uniform mat3 mat_n;

out VertexData {
	vec3 vertex_position;
	vec3 vertex;
	float material;
} vertexShader;


void main(void){
    vertexShader.vertex = vertex.xyz;
    vertexShader.vertex_position = (mat_mv * vertex).xyz;
    vertexShader.material = material;
    gl_Position = mat_p * mat_mv * vertex;

}
