#version 410

layout (points) in;
layout (triangle_strip, max_vertices = 400) out;

uniform mat4 mvp;

void main() {
    float i;
    float j;

    for (i = 0; i < 2.0; i++)
    {
        for (j = 0; j < 2.0; j++)
        {
            gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, j, 0);
            EmitVertex();

            gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, j, 0);
            EmitVertex();

            gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, -j, 0);
            EmitVertex();

            gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, -j, 0);
            EmitVertex();
        } 
    } 
    
    EndPrimitive();
}  