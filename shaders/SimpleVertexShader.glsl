#version 410 core

in vec3 position;
in vec3 color;
in vec2 uv;
in vec3 normal;

out vec3 _color;

uniform mat4	mvp;

void main() {
	gl_Position = mvp * vec4(position, 1);
	_color = color;
}
