#version 410

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;
layout (location = 3) in vec2 uv;

out vec3 _position;
out vec4 _color;
out vec3 _normal;
out vec2 _uv;
out vec3 _light;
out vec4 _eye;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform vec3 eye;
uniform vec3 light;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  _position = vec3(m * vec4(position, 1.0));
  _color = vec4(color, 255.0);
  _normal = mat3(v * m) * normal;
  _uv = uv;
  _light = light;
  _eye = vec4(eye, 1.0);
}