#version 410

in vec3 position;
in vec3 color;
in vec3 normal;

out vec4 _position;
out vec4 _color;
out vec4 _normal;
out vec4 _light;
out vec4 _eye;

uniform mat4 mvp;
uniform mat4 m;
uniform mat4 v;
uniform vec3 eye;
uniform vec3 light;
uniform float ambient_light;
uniform float specular_light;

void main() {
  gl_Position = mvp * vec4(position, 1.0);
  _position = m * vec4(position, 1.0);
  _color = vec4(color, 255.0);
  _normal = vec4(normal, 1.0) * inverse(v * m);
  _light = vec4(light, 1.0);
  _eye = vec4(eye, 1.0);
}