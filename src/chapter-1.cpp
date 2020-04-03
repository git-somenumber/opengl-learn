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


	const char* vertexSource = reader("./shaders/chapter-one.vert").c_str();
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vShader, 1, &vertexSource, NULL);
	glCompileShader(vShader);
	GLint vStatus;
	glGetShaderiv(vShader, GL_COMPILE_STATUS, &vStatus);
	if(vStatus!=GL_TRUE){
		printf("Vertex Shader not Compiled\n");
	}

	char vBuffer[512];
	glGetShaderInfoLog(vShader, 512, NULL, vBuffer);
	cout<<vBuffer;


	const char* fragmentSource = reader("./shaders/chapter-one.frag").c_str();
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fShader, 1, &fragmentSource, NULL);
	glCompileShader(fShader);
	GLint fStatus;
	glGetShaderiv(fShader, GL_COMPILE_STATUS, &fStatus);
	if(fStatus!=GL_TRUE){
		printf("Fragment Shader not compiled");
	}

	char fBuffer[512];
	glGetShaderInfoLog(fShader, 512, NULL, fBuffer);
	cout << fBuffer;

	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	// glBindFragDataLocation(shaderProgram, 0, "outColor");
	// glBindAttribLocation(shaderProgram, 10, "p");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	GLint proStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &proStatus);
	if(proStatus!=GL_TRUE){
		printf("Linking failed\n");
		char proInfo[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
		cout<<proInfo<<"\n";
	}

	GLuint vao, vertexBuffer;
	glGenVertexArrays(1, &vao);
	glGenBuffers(1,&vertexBuffer);
	glBindVertexArray(vao);

	float vertices[]={
		-0.5f,-0.5f,
		0.0f,0.0f,
		0.5f,0.5f
	};

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 3  * sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Getting positions from buffer into the program
	GLuint posLoc = glGetAttribLocation(shaderProgram, "p");
	printf("%i\n", posLoc);
	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(posLoc);
	
	glBindVertexArray(0);
	GLenum err;
	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
    }
	
	glDrawElements(GL_TRIANGLES, 3, GL_FLOAT, 0);

	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
		cout << gluErrorString(err) << "\n";
    }
	while(!glfwWindowShouldClose(window)){
		// glClearColor(1.0f,0.5f, 0.5f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_LINES, 0, 3);
    	glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
