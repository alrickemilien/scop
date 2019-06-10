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

  // vec4 specular;
  // vec4 viewDir;
  // vec4 reflectDir;  
  
  norm = normalize(_normal);

  lightDir = normalize(_light - _position);
  diffuse = max(dot(norm, lightDir), 0.0);

  // viewDir = normalize(_eye - _position);
  // reflectDir = reflect(-lightDir, _normal);
  // specular = vec4( specular_light * pow(max(dot(viewDir, reflectDir), 0.0), 32) * vec3(255.0, 255.0, 255.0), 1.0 );

  fragColour = (ambient_light + diffuse) * _color;

  fragColour.w = 255.0;
}