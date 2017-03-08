#version 400

in layout(location = 0) vec3 vertexPosition;

uniform vec3 uColor;

out vec3 color;

void main()
{
	color = uColor;
	gl_Position = vec4(vertexPosition, 1.0);
}