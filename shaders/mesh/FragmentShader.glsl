#version 410

out vec4 fragColour;

in vec3 _position;
in vec4 _color;
in vec3 _normal;
in vec3 _light;
in vec4 _eye;

uniform float ambient_light;
uniform float specular_light;

void main() {
  vec3  norm;
  vec3  lightDir;
  float diffuse;

  norm = normalize(_normal);

  lightDir = normalize(_light - _position);
  diffuse = max(dot(_normal, lightDir), 0.0);

  fragColour = (ambient_light + diffuse) * _color;

  fragColour.w = 255.0;
}