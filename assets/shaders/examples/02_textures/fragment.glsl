#version 330 core

out vec4 fragColor;

in vec4 vertex_color;
in vec2 texture_coords;

uniform float mix_factor;
// a sampler2D object is actually an integer referreing to GL_TEXTURE0, GL_TEXTURE1, GL_TEXTURE2, ...
uniform sampler2D texture_data_1;
uniform sampler2D texture_data_2;

void main()
{
    fragColor = mix(texture(texture_data_1, texture_coords), texture(texture_data_2, texture_coords), mix_factor) * vertex_color;
}