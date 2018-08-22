#version 330

layout(location = 0) in vec3 i_position;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectedMat;


void main()
{
	gl_Position = projectedMat * viewMat * modelMat * vec4(i_position, 1.0);
}