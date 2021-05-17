#version 400

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec2 VertexTexCoords;
layout (location = 2) in vec3 VertexNormal;

out vec3 normal;
out vec2 textureCoords;
out vec3 lightDirection;

uniform vec3 light;
uniform mat4 transform;

void main()
{
	lightDirection = light - VertexPosition;
	lightDirection = normalize(lightDirection);
	normal = VertexNormal;
	textureCoords = VertexTexCoords;
	gl_Position = transform * vec4(VertexPosition, 1.0);
}