#version 150 core
in vec4 p;
in vec3 color;
out vec3 vert_color;
uniform vec2 posOffset;
void main()
{
    gl_Position=vec4(p.x+posOffset.x, p.y+posOffset.y, p.z, p.w);
    vert_color = color;
}
