#version 420

in layout(location = 0) vec3 vertexPosition;
in layout(location = 2) vec3 vertexTexture;

out vec2 textureCoords;

void main()
{
	gl_Position = vec4(vertexPosition, 1.0);
	textureCoords =vertexTexture.xy;
}