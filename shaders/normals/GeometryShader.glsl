#version 410 core

layout (triangles) in;
layout (line_strip, max_vertices = 6) out;

in VS_OUT {
    vec3 position;
    vec3 normal;
} gs_in[];

uniform mat4 mvp;

const float MAGNITUDE = 0.2;

void GenerateLine(int index)
{
    gl_Position = gl_in[index].gl_Position;
    EmitVertex();
    gl_Position = mvp * vec4(gs_in[index].position + normalize(gs_in[index].normal) * MAGNITUDE, 1.0);
    EmitVertex();
    EndPrimitive();
}

void main()
{
    GenerateLine(0); // first vertex normal
    GenerateLine(1); // second vertex normal
    GenerateLine(2); // third vertex normal
} 