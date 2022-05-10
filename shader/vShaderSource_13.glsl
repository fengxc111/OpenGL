#version 430 core

layout( location = 0 ) in vec2 vPos;
layout( location = 1 ) in vec3 vColor;
out vec3 fColor;
uniform vec2 offsets[100];
uniform mat4 transform;

void main() {
	vec2 offset = offsets[gl_InstanceID];
	gl_Position = transform * vec4(vPos + offset, 0.0, 1.0);
	fColor = vColor;
}