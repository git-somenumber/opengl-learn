#version 150 core
out vec4 outColor;
in vec2 TexCoord;
in vec3 ourColor;
uniform sampler2D tex;
void main()
{
    outColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
}