#version 150 core
uniform vec3 triangleCol;
out vec4 outColor;
void main()
{
    outColor = vec4(triangleCol, 1.0);
}