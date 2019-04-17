#version 410

uniform vec4 _color;
out vec4 fragColour;

void main() {
  fragColour = _color;
}