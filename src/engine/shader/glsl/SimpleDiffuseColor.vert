#version 400

in layout(location = 0) vec3 vertexPosition;

uniform vec3 uColor;
uniform mat4 transformationMatrix;
uniform mat4 projectionMatrix;

out vec3 color;

void main()
{
	vec4 worldPosition = projectionMatrix * transformationMatrix * vec4(vertexPosition,1.0);
	color = uColor;
	gl_Position = worldPosition;
}