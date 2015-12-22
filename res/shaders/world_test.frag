#version 150

uniform sampler2D texture0;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform sampler2DArray texture3;

in vec3 vertex;
in vec3 frag_normal;
in vec3 frag_position;
in float material;

vec3 lightPos = vec3(1,6,1);

vec4 lambient = vec4(0.9, 0.9, 0.9, 1);
vec4 ldiffuse = vec4(0.4, 0.4, 0.4, 1);

void main(void)
{
    vec4 color;
    vec3 dirToLight = normalize(lightPos - frag_position);
    vec3 normal = normalize(frag_normal);
    float intensity = max(0.0, dot(dirToLight, normal));

    vec3 tex = vertex;
    int layer = int(max(0, min(8 -1, floor(material - 1 + 0.5))));


    if (frag_normal.y > 0.9)
    {
        color = texture(texture3, vec3(tex.xz, layer));
        //if (material > 200) color = texture(texture3, vec3(tex.xz, 0));
        //else color = texture(texture3, vec3(tex.xz, 2));
    }

    if (frag_normal.y < 0.9)
    {
        color = texture(texture3, vec3(tex.xz, layer));
        //if (material > 200) color = texture(texture3, vec3(tex.xz, 1));
        //else color = texture(texture3, vec3(tex.xz, 2));
    }

    if (abs(frag_normal.x) > 0.9)
    {
        color = texture(texture3, vec3(tex.yz, layer));
        //if (material > 200) color = texture(texture3, vec3(tex.yz, 1));
        //else color = texture(texture3, vec3(tex.yz, 2));
    }

    if (abs(frag_normal.z) > 0.9)
    {
        color = texture(texture3, vec3(tex.xy, layer));
     //   if (material > 200) color = texture(texture3, vec3(tex.xy, 1));
       // else color = texture(texture3, vec3(tex.xy, 2));
    }


    gl_FragColor = color * (lambient + intensity * ldiffuse);
}

