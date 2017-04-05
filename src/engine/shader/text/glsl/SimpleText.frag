#version 420

in vec2 textureCoords;

uniform sampler2D fontTexture;
uniform vec4 matColor;

out vec4 fragColor;

void main()
{
	fragColor = vec4(matColor.xyz, texture(fontTexture, textureCoords).a);
}