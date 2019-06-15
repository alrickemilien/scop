#version 410

in vec3 position;
in vec3 color;
in vec3 normal;

out VS_OUT {
    vec4 normal;
} vs_out;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform mat4 p;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  mat4 normal_matrix = transpose(inverse(m));
  vs_out.normal = normalize(p * v * normal_matrix * vec4(normal, 0.0));
}