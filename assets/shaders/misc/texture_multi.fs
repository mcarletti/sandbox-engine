#version 330 core

out vec4 fragColor;

in vec4 vertexColor;
in vec2 textureCoords;

uniform sampler2D textureData1;
uniform sampler2D textureData2;
uniform float textureMixValue;

void main()
{
    //fragColor = mix(texture(textureData1, textureCoords), texture(textureData2, textureCoords), 0.5);
    fragColor = mix(texture(textureData1, textureCoords), texture(textureData2, textureCoords), textureMixValue);
}