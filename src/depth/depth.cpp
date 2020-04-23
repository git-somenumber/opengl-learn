#include<stdio.h>
#include"../shader.cpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/trigonometric.hpp"
#include<GL/glew.h>
#include<glfw3.h>
#define STB_IMAGE_IMPLEMENTATION
#include"stb_image.h"
#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

void glfw_call(GLFWwindow * window, int a , int b, int c, int d)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}
void mat(GLuint program)
{
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));


	glm::mat4 viewMat = glm::mat4(1.0f);


	glm::mat4 projMat = glm::mat4(1.0f);


	GLuint model = glGetAttribLocation(program, "model");
	GLuint view = glGetAttribLocation(program, "view");
	GLuint proj = glGetAttribLocation(program, "proj");
}
int main()
{
    glfwInit();
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "One", NULL, NULL);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	if (glewInit()) {
    	fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
	}
	if (!window)
	{
    	// Window or OpenGL context creation failed
		printf("Failed to create window");
	}
    glfwPollEvents();
    glfwSetKeyCallback(window, glfw_call);

    // ============ Shader-Init ============ //
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    createShader((char*)"./depth.vert", vShader);
    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    createShader((char*)"./depth.frag", fShader);

    // ============ Program-Init ============ //
    GLuint program = glCreateProgram();
    glAttachShader(program, vShader);
    glAttachShader(program, fShader);
    glLinkProgram(program);
    GLint proStatus;
    glGetProgramiv(program, GL_LINK_STATUS, &proStatus);
    if(proStatus!=GL_TRUE)
    {
	printf("Linking failed\n");
    }
    char proInfo[512];
    glGetProgramInfoLog(program, 512, NULL, proInfo);
    std::cout<<proInfo<<"\n";

    // =========== Buffer - Init ==============//
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    float vertices[] = {
	    0.5f, 0.5f, 1.0f,    1.0f, 1.0f, 0.0f,
	    0.5f, -0.5f, 1.0f,   1.0f, 0.0f, 0.0f,
	    -0.5f, -0.5f, 1.0f,  0.0f, 0.0f, 1.0f,
	    -0.5f, 0.5f, 1.0f,   0.0f, 1.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint indices[] = {
    	0 , 1, 2,
	    2 , 3, 0
    };
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Matrix init
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f, -1.0f));
    glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f,100.0f);

    // Locations of matrices
    GLint model = glGetUniformLocation(program, "model");
    GLint view = glGetUniformLocation(program, "view");
    GLint proj = glGetUniformLocation(program, "proj");
    std::cout<<view<<"\n";

    // Providing matrices
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{two}"<< "\n";
    }
    glUseProgram(program);
    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{three}"<< "\n";
    }
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(projMat));
    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{one}"<< "\n";
    }

    // Activating program and providing buffer location
    GLuint posLoc = glGetAttribLocation(program, "position");
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(0*sizeof(float)));
    glEnableVertexAttribArray(posLoc);
   
    GLuint texLoc = glGetAttribLocation(program, "texCoord");
    glVertexAttribPointer(texLoc, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float))); 
    glEnableVertexAttribArray(texLoc);

    // ================ texture-init ================== //
    GLuint tex;
    glGenTextures( 1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLint width, height, nrChannels;
    unsigned char* data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    stbi_image_free(data);


    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "\n";
    }
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	    glUseProgram(program);
	    glBindVertexArray(vao);
	    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "\n";
    }
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
