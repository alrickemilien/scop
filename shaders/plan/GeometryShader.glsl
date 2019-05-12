#version 410

uniform int max;

layout (points) in;
layout (points, max_vertices = 10000) out;

in vec3 _color[];
out vec3 fs_color;

void main() {
    fs_color = _color[0];
    
    for(int i = 0; i < max; i++) {
        for(int j = 0; j < max; j++) {
            gl_Position = vec4(gl_in[0].gl_Position.x + j, 0, gl_in[0].gl_Position.z + i);
            EmitVertex();

            gl_Position = vec4(gl_in[0].gl_Position.x + j, 0, gl_in[0].gl_Position.z - i);
            EmitVertex();

            gl_Position = vec4(gl_in[0].gl_Position.x - j, 0, gl_in[0].gl_Position.z + i);
            EmitVertex();

            gl_Position = vec4(gl_in[0].gl_Position.x - j, 0, gl_in[0].gl_Position.z - i);
            EmitVertex();
        }
    }

    EndPrimitive();
}