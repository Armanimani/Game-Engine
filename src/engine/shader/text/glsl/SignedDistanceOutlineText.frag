#version 420

in vec2 textureCoords;

uniform sampler2D fontTexture;
uniform vec4 matColor;
uniform float matFontWidth;
uniform float matFontEdge;

uniform vec4 matOutlineColor;
uniform float matOutlineWidth;
uniform float matOutlineEdge;
uniform float matOutlineOffsetX;
uniform float matOutlineOffsetY;


out vec4 fragColor;

void main()
{
	float distance = 1.0 - texture(fontTexture, textureCoords).a;
	float alpha = 1.0 - smoothstep(matFontWidth, matFontWidth + matFontEdge, distance);

	float distance2 = 1.0 - texture(fontTexture, textureCoords + vec2(matOutlineOffsetX, matOutlineOffsetY)).a;
	float alpha2 = 1.0 - smoothstep(matOutlineWidth, matOutlineWidth + matOutlineEdge, distance2);

	float overallAlpha = alpha + (1.0 - alpha) * alpha2;
	vec3 overallColor = mix(matOutlineColor.xyz, matColor.xyz, alpha * matColor.a / alpha2 / matOutlineColor.a); 

	fragColor = vec4(overallColor, overallAlpha);
}