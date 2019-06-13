#version 410

in vec4 _position;
in vec4 _color;
in vec4 _normal;
in vec4 _light;
in vec4 _eye;

out vec4 fragColour;

uniform float ambient_light;
uniform float specular_light;

void main() {
  vec4 norm;
  vec4 lightDir;
  float diffuse;

  norm = normalize(_normal);

  lightDir = normalize(_light - _position);
  diffuse = max(dot(norm, lightDir), 0.0);

  fragColour = (ambient_light + diffuse) * _color;

  fragColour.w = 255.0;
}