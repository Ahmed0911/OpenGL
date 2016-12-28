#version 400

in vec4 ex_Color;
// Interpolated values from the vertex shaders
in vec2 UV;
out vec4 out_Color;

uniform sampler2D myTexture;

void main(void)
{
  //out_Color = ex_Color;
  //out_Color = vec4(UV.y, UV.y, UV.y, 1.0); //Reverses the order.
  out_Color = texture( myTexture, UV );
}
