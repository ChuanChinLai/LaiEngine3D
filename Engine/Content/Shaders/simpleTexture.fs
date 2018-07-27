#version 330

in vec4 vertexColor;
in vec2 vertexUV;

out vec4 o_color;

uniform sampler2D Texture0;
uniform sampler2D Texture1;

void main()
{
   o_color = mix(texture(Texture0, vertexUV), texture(Texture1, vertexUV), 0.5);
}