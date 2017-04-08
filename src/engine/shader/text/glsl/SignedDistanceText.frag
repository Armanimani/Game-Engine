#version 420

in vec2 textureCoords;

uniform sampler2D fontTexture;
uniform vec4 matColor;
uniform float matFontWidth;
uniform float matFontEdge;

out vec4 fragColor;

void main()
{
	float distance = 1.0 - texture(fontTexture, textureCoords).a;
	float alpha = 1.0 - smoothstep(matFontWidth, matFontWidth + matFontEdge, distance);
	fragColor = vec4(matColor.xyz, alpha * matColor.a);
}