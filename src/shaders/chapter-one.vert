#version 150 core
in vec4 p;
in vec3 color;
out vec3 vert_color;
void main()
{
    gl_Position=p;
    vert_color = color;
}
