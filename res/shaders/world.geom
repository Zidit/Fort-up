
#version 150


layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;


in VertexData {
	vec3 vertex_position;
	vec3 vertex;
	float material;
} vertexShader[3];

out vec3 frag_normal;
out vec3 frag_position;
out vec3 vertex;
out float material;


void main()
{

    vec3 d1 = vertexShader[1].vertex - vertexShader[0].vertex;
    vec3 d2 = vertexShader[2].vertex - vertexShader[0].vertex;
    vec3 normal = normalize(cross(d1,d2));


	for(int i = 0; i < gl_in.length(); i++)
  	{
     		// copy attributes
   		gl_Position = gl_in[i].gl_Position;

 		vertex = vertexShader[i].vertex;
		frag_position = vertexShader[i].vertex_position;
		material = vertexShader[i].material;

		frag_normal = normal;

        EmitVertex();
  	}

}



