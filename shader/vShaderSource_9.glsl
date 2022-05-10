#version 430 core

layout( location = 0 ) in vec3 vPosition;
layout( location = 1 ) in vec3 vColor;
out vec3 tColor;
uniform float offset;

void main() {
	gl_Position = vec4(vPosition.x + offset, -vPosition.y, vPosition.z, 1.0);
	tColor = vColor;
}