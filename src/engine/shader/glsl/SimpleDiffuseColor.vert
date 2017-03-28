#version 420

in layout(location = 0) vec3 vertexPosition;

layout(std140, binding = 0) uniform matricies
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform mat4 transformationMatrix;

uniform vec3 uColor;

out vec3 color;

void main()
{
	vec4 worldPosition = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertexPosition,1.0);
	color = uColor;
	gl_Position = worldPosition;
}