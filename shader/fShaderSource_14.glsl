#version 430 core
out vec4 fColor;
in vec3 tColor;
in vec2 tTexture;

uniform sampler2D myTexture;

void main() {
	fColor = texture(myTexture, tTexture);
}