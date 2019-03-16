#version 410 core

in vec3			position;
in vec3			color;
in vec2			uv;
in vec3			normal;

out vec3 _color;
out vec2 _uv;
out vec3 _normal;

uniform mat4	mvp;

void main() {
	gl_Position = mvp * vec4(position, 1);
	_color = color;
	_uv = uv;
	_color = color;
}
