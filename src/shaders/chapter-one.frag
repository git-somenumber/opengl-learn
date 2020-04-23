#version 150 core
in vec3 vert_color;
out vec4 outColor;
void main()
{
    outColor = vec4(vert_color, 1.0);
}
