#version 150 core
in vec3 p;
in vec3 color;

out vec3 vert_color;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

void main()
{
    gl_Position = proj * view * model * vec4(p, 1.0);
    vert_color = color;
}
