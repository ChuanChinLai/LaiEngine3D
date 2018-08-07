#version 330

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 o_color;

uniform sampler2D Ambient1;
uniform sampler2D Diffuse1;
uniform sampler2D Specular1;
uniform sampler2D Bump1;

void main()
{
    o_color = texture(Diffuse1, vertexUV) + texture(Bump1, vertexUV);
//	o_color = vertexColor;
}