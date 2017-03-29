#version 420

in vec4 color;

out vec4 fragColor;

layout (std140, binding = 5) uniform gammaCorrectionBlock
{
	float gammaCorrection;
};

void main()
{
	fragColor = vec4(pow(color.xyz, vec3(gammaCorrection)), color.a);
}