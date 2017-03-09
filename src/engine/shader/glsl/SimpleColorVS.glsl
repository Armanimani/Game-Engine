#version 400

in layout(location = 0) vec3 vertexPosition;
in layout(location = 3) vec3 vertexColor;

uniform mat4 transformationMatrix;

out vec3 color;

void main()
{
	vec4 worldPosition = transformationMatrix * vec4(vertexPosition,1.0);
	color = vertexColor;
	gl_Position = worldPosition;
}