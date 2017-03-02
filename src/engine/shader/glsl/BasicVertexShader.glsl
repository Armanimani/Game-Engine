#version 400

in layout(location = 0) vec3 vertexPosition;
in layout(location = 3) vec3 vertexColor;

out vec3 color;

void main()
{
	color = vertexColor;
	//color = vec3(1.0, 1.0, 1.0);
	gl_Position = vec4(vertexPosition, 1.0);
}