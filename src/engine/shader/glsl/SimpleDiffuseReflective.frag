#version 400

in vec3 color;
in float lightIntensity;
out vec4 fragColor;

void main()
{
	fragColor = vec4(color * lightIntensity, 1.0);
}