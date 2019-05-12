#version 410

in vec3 position;
in vec3 color;

out vec4 _color;

uniform mat4 mvp;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  _color = vec4(color, 255.0);
}