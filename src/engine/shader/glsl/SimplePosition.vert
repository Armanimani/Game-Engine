#version 420

in layout(location = 0) vec3 vertexPosition;

layout(std140, binding = 0) uniform matricies
{
	mat4 projectionMatrix;
	mat4 viewMatrix;
};

uniform mat4 transformationMatrix;

out vec3 color;

void main()
{
	vec4 worldPosition = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertexPosition,1.0);
	color = vec3(1.0, 1.0, 1.0);
	gl_Position = worldPosition;
}