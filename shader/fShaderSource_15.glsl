#version 430 core
out vec4 fColor;
in vec3 tColor;
in vec2 tTexture;
uniform sampler2D myTexture1;
uniform sampler2D myTexture2;

void main() {
	fColor = mix(texture(myTexture1, tTexture), texture(myTexture2, tTexture), 0.45) * vec4(tColor, 0.1);
}