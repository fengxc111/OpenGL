#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

//uniform sampler2D ourTexture;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float alpha;

void main()
{
    //FragColor = texture(ourTexture, TexCoord);
//FragColor = texture(ourTexture, TexCoord) * vec4(ourColor, 1.0);
//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
//FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(-TexCoord.x, TexCoord.y)), 0.2);
FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), alpha);
}