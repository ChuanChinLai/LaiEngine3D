#version 330

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 o_color;

uniform sampler2D texture_diffuse1;
 
void main()
{
    o_color = texture(texture_diffuse1, vertexUV);
//	o_color = vertexColor;
}