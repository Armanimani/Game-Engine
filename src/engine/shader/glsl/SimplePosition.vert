#version 400

in layout(location = 0) vec3 vertexPosition;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 color;

void main()
{
	vec4 worldPosition = projectionMatrix * viewMatrix * transformationMatrix * vec4(vertexPosition,1.0);
	color = vec3(1.0, 1.0, 1.0);
	gl_Position = worldPosition;
}