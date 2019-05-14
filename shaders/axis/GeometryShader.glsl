#version 410

layout (points) in;
layout (line_strip, max_vertices = 7) out;

out vec4 axis[];

uniform mat4 mvp;

void main() {
    // Origin
    gl_Position = gl_in[0].gl_Position;
    axis[0] = gl_in[0].gl_Position;
    EmitVertex();

    // X AXIS
    gl_Position = gl_in[0].gl_Position + mvp * vec4(3, 0, 0, 0);
    axis[1] = vec4(3, 0, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();

    // Y AXIS
    gl_Position = gl_in[0].gl_Position + mvp * vec4(0, 3, 0, 0);
    axis[2] = vec4(0, 3, 0, 0);
    EmitVertex();

    gl_Position = gl_in[0].gl_Position;
    EmitVertex();
    
    // Z AXIS
    gl_Position = gl_in[0].gl_Position + mvp * vec4(0, 0, 3, 0);
    axis[3] = vec4(0, 0, 3, 0);
    EmitVertex();

    EndPrimitive();
}  