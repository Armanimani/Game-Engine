#version 400

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

uniform vec3 uColor;
uniform float uKa;
uniform float uKd;
uniform float uKs;
uniform float uShininess;

uniform vec3 uLight_position;
uniform float uLight_ambientIntensity;
uniform float uLight_diffuseIntensity;
uniform float uLight_specularIntensity;

out vec3 color;
out float lightIntensity;

void main()
{
	float ambient = uKa * uLight_ambientIntensity;
	mat4 modelViewMatrix = viewMatrix * transformationMatrix;
	vec4 worldPosition = projectionMatrix * modelViewMatrix * vec4(vertexPosition,1.0);
	vec4 tnorm = normalize(normalMatrix * vec4(vertexNormal, 0.0));
	vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
	vec4 s = normalize(vec4(uLight_position, 0.0) - eyeCoords);
//	float diffuse = (uLight_diffuseIntensity * uKd * max(dot(s, tnorm), 0.0));
	lightIntensity = ambient;
	color = uColor;
	gl_Position = worldPosition;

}