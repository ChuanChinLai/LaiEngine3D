#version 330
layout(location = 0) in vec3 i_position;
layout(location = 1) in vec3 i_color;

out vec4 vertexColor;
 
void main()
{
  gl_Position = Translation * Rotation * Scale * vec4(i_position, 1.0);
  vertexColor = vec4(i_color, 1.0);
}