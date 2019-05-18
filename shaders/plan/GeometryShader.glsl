#version 410

layout (points) in;
layout (line_strip, max_vertices = 400) out;

// points
// line_strip
// triangle_strip

// https://stackoverflow.com/questions/27467810/using-line-strip-adjacency-with-the-geometry-shader

uniform mat4 mvp;

void main() {
    float i = 4;
    float j = 4;

    gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, j, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, j, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, -j, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, -j, 0);
    EmitVertex();

    //for (i = 0; i < 5.0; i++)
    //{
    //    for (j = 0; j < 5.0; j++)
    //    {
    //        gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, j, 0);
    //        EmitVertex();
//
    //        gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, j, 0);
    //        EmitVertex();
//
    //        gl_Position = gl_in[0].gl_Position + mvp * vec4(i, 0, -j, 0);
    //        EmitVertex();
//
    //        gl_Position = gl_in[0].gl_Position + mvp * vec4(-i, 0, -j, 0);
    //        EmitVertex();
    //    } 
    //} 
    
    EndPrimitive();
}  