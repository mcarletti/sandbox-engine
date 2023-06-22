#version 330 core

layout (location = 0) in vec3 position;
layout (location = 3) in vec2 uv_coords;

out vec2 texture_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = vec4(position.xyz, 1.0) * model * view * projection;
    texture_coords = uv_coords;
}