#version 330 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 color;
layout (location = 2) in vec2 texCoord;

out vec3 Color;
out vec2 TexCoord;
void main()
{
	gl_Position=vec4(pos, 1.0);
	TexCoord = texCoord;
	Color = color;
}
