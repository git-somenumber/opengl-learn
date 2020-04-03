#include<GL/glew.h>
#include<glfw3.h>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include"reader.cpp"

using std::cout;
using std::ifstream;
using std::string;
using std::getline;

void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}



int main(){
	
	if(!glfwInit()){
		printf("Error initialising glfw");
	}

	string a = reader("./file.txt");
	
	glfwSetErrorCallback(error_callback);
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);

	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

	// Window creation and hints also check if window creation failed
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
	glewExperimental = GL_TRUE;
	glfwMakeContextCurrent(window);
	glewInit();
	if (!window)
	{
    		// Window or OpenGL context creation failed
		printf("Failed to create window");
	}
	
	glfwShowWindow(window);
	glfwSwapBuffers(window);


	GLuint vertexBuffer;
	glGenBuffers(1,&vertexBuffer);

	printf("%p\n", &vertexBuffer);

	float vertices[]={
		-0.5f,-0.5f,
		0.0f,0.0f,
		0.5f,0.5f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Shaders
	// const char* vertexSource = R"(
	// #version 150 core

   	//  in vec2 position;

   	//  void main()
    // 	{
    //     	gl_Position = vec4(position, 0.0, 1.0);
    // 	}
	// )";

	// TODO:Commented for testing reader
	// GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	// glShaderSource(vShader, 1, &vertexSource, NULL);
	// glCompileShader(vShader);
	// GLint vStatus;
	// glGetShaderiv(vShader, GL_COMPILE_STATUS, &vStatus);
	// if(vStatus!=GL_TRUE){
	// 	printf("Vertex Shader not Compiled");
	// }

	// const char* fragmentSource = R"(
	// 	#version 150 core
	// 	out vec4 outColor;

	// 	void main()
	// 	{
	// 		outColor = vec4(1.0,1.0,1.0,1.0);
	// 	}
	// )";

	// TODO:Commented for testing reader
	// GLuint fShader = glCreateShader(GL_VERTEX_SHADER);
	// glShaderSource(fShader, 1, &fragmentSource, NULL);
	// glCompileShader(fShader);
	// GLint fStatus;
	// glGetShaderiv(fShader, GL_COMPILE_STATUS, &fStatus);
	// if(fStatus!=GL_TRUE){
	// 	printf("Fragment Shader not compiled");
	// }

	// GLuint shaderProgram = glCreateProgram();
	// glAttachShader(shaderProgram, vShader);
	// glAttachShader(shaderProgram, fShader);
	// glLinkProgram(shaderProgram);
	// glUseProgram(shaderProgram);

	// // Getting positions from buffer into the program
	// GLuint posLoc = glGetAttribLocation(shaderProgram, "position");
	

	while(!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
    		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
