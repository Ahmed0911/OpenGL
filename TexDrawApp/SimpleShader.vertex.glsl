#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec2 in_UV;
out vec4 ex_Color;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(void)
{
  gl_Position = in_Position;
  ex_Color = in_Color;
  UV = in_UV;
}
