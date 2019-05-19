#version 410

layout (points) in;
layout (line_strip, max_vertices = 256) out;

// points
// line_strip
// triangle_strip

// https://stackoverflow.com/questions/27467810/using-line-strip-adjacency-with-the-geometry-shader

uniform mat4 mvp;

void main() {
    float j;

    float X = 5;

    for (j = -X; j < X + 1; j++)
    {
        gl_Position = gl_in[0].gl_Position + mvp * vec4(X, 0, j, 0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + mvp * vec4(-X, 0, j, 0);
        EmitVertex();

        EndPrimitive();
    } 

    for (j = -X; j < X + 1; j++)
    {
        gl_Position = gl_in[0].gl_Position + mvp * vec4(j, 0, X, 0);
        EmitVertex();

        gl_Position = gl_in[0].gl_Position + mvp * vec4(j, 0, -X, 0);
        EmitVertex();

        EndPrimitive();
    }
}  