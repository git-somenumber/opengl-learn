#version 330 core
in vec3 pos;
in vec3 color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

out vec3 Color;
void main()
{
    gl_Position = proj*view*model*vec4(pos, 1.0);
    Color = color;
}