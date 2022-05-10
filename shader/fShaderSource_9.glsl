#version 430 core

in vec3 tColor;
out vec4 fColor;

void main() {
	fColor = vec4(tColor,1.0);
};