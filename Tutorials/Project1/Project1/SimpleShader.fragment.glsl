#version 400

in vec4 ex_Color;
// Interpolated values from the vertex shaders
in vec2 UV;
out vec4 out_Color;

uniform sampler2D myTextureSampler1;
uniform sampler2D myTextureSampler2;

void main(void)
{
  //out_Color = ex_Color;
  //out_Color = vec4(UV.x, UV.y, 0, 1.0); //Reverses the order.
  out_Color = mix( texture( myTextureSampler1, UV ), texture( myTextureSampler2, UV ), 0.6);
}
