#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;

uniform bool use_flat_color = false;

out vec4 vertexColor;

void main()
{
    gl_Position = vec4(position.xyz, 1.0);

    if (use_flat_color)
        vertexColor = vec4(1.0, 0.0, 1.0, 1.0);
    else
        vertexColor = vec4(color, 1.0);
}