#version 330 core
in vec3 position;
in vec3 texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec2 TexCoord;
void main()
{
	gl_Position = proj*view*model*vec4(position, 1.0);
	// gl_Position = vec4(position, 1.0);
	TexCoord = vec2(texCoord.x, texCoord.y);
}
