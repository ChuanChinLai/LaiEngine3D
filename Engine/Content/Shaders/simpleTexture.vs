#version 330

layout(location = 0) in vec3 i_position;
layout(location = 1) in vec3 i_color;
layout(location = 2) in vec2 i_UV;

out vec4 vertexColor;
out vec2 vertexUV;
 
void main()
{
  gl_Position = vec4(i_position, 1.0);
  vertexColor = vec4(i_color, 1.0);
  vertexUV = i_UV;
}