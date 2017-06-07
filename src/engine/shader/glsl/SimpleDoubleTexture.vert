#version 420

const int MAX_LIGHTS = 20;

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;
in layout(location = 2) vec3 vertexTexture;

uniform mat4 transformationMatrix;
uniform mat3 normalMatrix;

out vec3 surfaceNormal;
out vec4 worldPosition;
out vec2 textureCoords;

layout(std140, binding = 0) uniform matriciesBlock
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

void main()
{
	worldPosition = transformationMatrix * vec4(vertexPosition, 1.0);
	surfaceNormal = normalize(normalMatrix * vertexNormal);
	gl_Position =  projectionMatrix * viewMatrix * worldPosition;
	textureCoords =vertexTexture.xy;
}