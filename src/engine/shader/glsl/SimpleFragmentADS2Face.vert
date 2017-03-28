#version 420

const int MAX_LIGHTS = 20;

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;

layout(std140, binding = 0) uniform matricies
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform mat4 transformationMatrix;

out vec3 surfaceNormal;
out vec4 worldPosition;

void main()
{
	worldPosition = transformationMatrix * vec4(vertexPosition, 1.0);
	surfaceNormal = normalize((transformationMatrix * vec4(vertexNormal, 0.0)).xyz);
	gl_Position =  projectionMatrix * viewMatrix * worldPosition;;
}