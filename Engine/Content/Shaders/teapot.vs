#version 330

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec3 i_normal;
layout(location = 2) in vec2 i_UV;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projectedMat;

out vec3 vertexNormal_worldSpace;
out vec3 vertexPosition_worldSpace;
out vec2 vertexUV;
 
void main()
{
    vertexUV = i_UV;
  
    vertexNormal_worldSpace   = vec3(transpose(inverse(modelMat)) * vec4(i_normal, 1.0));
	
    vertexPosition_worldSpace = vec3(modelMat * vec4(i_position, 1.0));
	
    gl_Position = projectedMat * viewMat * vec4(vertexPosition_worldSpace, 1.0);
	
}