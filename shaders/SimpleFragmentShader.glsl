#version 410 core

in vec3 _color;

out vec4 color;

void main() {
  gl_FragColor = vec4(_color, 1.0);
}
