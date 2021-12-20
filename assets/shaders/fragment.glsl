#version 330 core

out vec4 fragColor;

in vec3 vertexWorldLoc;
in vec3 vertexNormal;
in vec4 vertexColor;
in vec2 textureCoords;

uniform sampler2D textureData1;
uniform sampler2D textureData2;
uniform float textureMixValue;

uniform vec3 lightPos;
uniform vec3 lightColor;

uniform vec3 cameraPos;

void main()
{
    vec4 objectColor = mix(texture(textureData1, textureCoords), texture(textureData2, textureCoords), textureMixValue);

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 normal = normalize(vertexNormal);
    vec3 lightDir = normalize(lightPos - vertexWorldLoc);  
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5;
    vec3 viewDir = normalize(cameraPos - vertexWorldLoc);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    fragColor = vec4((ambient + diffuse + specular) * objectColor.rgb, 1.0);
}