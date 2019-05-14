#version 410

in vec4 axis;

out vec4 fragColour;

void main() {
  if (axis.x > 0) {
     fragColour = vec4(0, 0, 1, 1);
  }
  
  if (axis.y > 0) {
    fragColour = vec4(0, 1, 0, 1);
  }
  
  if (axis.z > 0) {
    fragColour = vec4(1, 0, 0, 1);
  }
}