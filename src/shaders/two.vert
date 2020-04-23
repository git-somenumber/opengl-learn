#version 150 core
in vec3 position;
in vec2 texCoord;
in vec3 color;

out vec2 TexCoord;
out vec3 ourColor;
void main()
{
    gl_Position =  vec4(position, 0.0);
    TexCoord = texCoord;
    ourColor = color;
}