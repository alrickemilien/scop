#version 410 core

out vec3 _color;
out vec3 _uv;
out vec3 _normal;

out vec4 color;

void main() {
  color = vec4(_color, 1.0);
}
