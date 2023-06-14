#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoords;

out vec3 vertexWorldLoc;
out vec3 vertexNormal;
out vec4 vertexColor;
out vec2 textureCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    vertexWorldLoc = vec3(model * vec4(position.xyz, 1.0));
    // per risolvere il problema della scalatura non lineare,
    // la normale va moltiplicata per la trasposta dell'inversa
    // della matrice "superiore" (rotazione) della matrice model
    vertexNormal = mat3(transpose(inverse(model))) * normal;
    vertexColor = vec4(color, 1.0);
    textureCoords = texCoords;

    gl_Position = projection * view * vec4(vertexWorldLoc, 1.0);
}