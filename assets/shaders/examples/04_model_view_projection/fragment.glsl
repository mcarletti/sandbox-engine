#version 330 core

out vec4 fragColor;

in vec2 texture_coords;

uniform sampler2D texture_data;

void main()
{
    fragColor = texture(texture_data, texture_coords);
}