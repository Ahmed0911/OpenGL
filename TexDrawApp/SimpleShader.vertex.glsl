#version 400

layout(location=0) in vec4 in_Position;
layout(location=1) in vec4 in_Color;
layout(location=2) in vec2 in_UV;

out vec4 ex_Color;
out vec2 UV;

uniform mat4 TransMatrix;

void main(void)
{
	gl_Position = TransMatrix * in_Position;
	//gl_Position = in_Position;
	ex_Color = in_Color;
	UV = in_UV;
}
