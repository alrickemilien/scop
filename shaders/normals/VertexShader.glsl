#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;

out VS_OUT {
    vec3 position;  
    vec3 normal;
} vs_out;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  vs_out.position = position;
  vs_out.normal = normal;
}