#version 330 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;

void main()
{
//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), alpha);
FragColor = mix(texture(texture2, TexCoord), texture(texture1, TexCoord), alpha);
//FragColor = texture(texture1, TexCoord);
}