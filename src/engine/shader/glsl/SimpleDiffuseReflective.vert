#version 400

in layout(location = 0) vec3 vertexPosition;
in layout(location = 1) vec3 vertexNormal;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 normalMatrix;

uniform vec3 uColor;
uniform float uKd;
uniform float uLight_intensity;
uniform vec3 uLight_position;

out vec3 color;
out float lightIntensity;

void main()
{
	mat4 modelViewMatrix = viewMatrix * transformationMatrix;
	vec4 worldPosition = projectionMatrix * modelViewMatrix * vec4(vertexPosition,1.0);
	vec4 tnorm = normalize(normalMatrix * vec4(vertexNormal, 0.0));
	vec4 eyeCoords = modelViewMatrix * vec4(vertexPosition, 1.0);
	vec4 s = normalize(vec4(uLight_position, 0.0) - eyeCoords);
	lightIntensity = (uLight_intensity * uKd * max(dot(s, tnorm), 0.0));
	color = uColor;
	gl_Position = worldPosition;

}