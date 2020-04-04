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

void message_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, GLchar const* message, void const* user_param)
{
	
	std::cout << "source: "<< source << ", Type:  " << type << ", ID: "<< id << ",Severity: "<< severity << ", Message: " << ": " << message << '\n';
}

void createShader(char* sourceFile, GLuint shader){
	const char* source = reader(sourceFile).c_str();
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);
	GLint status;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if(status != GL_TRUE){
		cout << "Failed to compile shader" << sourceFile;
	}
	char info[512];
	glGetShaderInfoLog(shader, 512, NULL, info);
	cout << info;
}


int main(){
	
	if(!glfwInit()){
		printf("Error initialising glfw");
	}
	
//	glfwSetErrorCallback(error_callback);
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);

	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

	// Window creation and hints also check if window creation failed
	glfwWindowHint(GLFW_VISIBLE, GLFW_TRUE);
	glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Title", NULL, NULL);
    glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
    	fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
	}
	if (!window)
	{
    	// Window or OpenGL context creation failed
		printf("Failed to create window");
	}
	
	glfwShowWindow(window);

	int width, height;
    glfwGetFramebufferSize(window, &width, &height);  
    glViewport(0, 0, width, height);

	// ================= Shaders for program - 1 ============== //
	// Vertex Shader 1
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	createShader("./shaders/chapter-one.vert", vShader);
	// Fragment Shader 1
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	createShader("./shaders/chapter-one.frag", fShader);


	// ================ Program - 1 - Setup ====================// 
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vShader);
	glAttachShader(shaderProgram, fShader);
	glLinkProgram(shaderProgram);
	GLint proStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &proStatus);
	if(proStatus!=GL_TRUE){
		printf("Linking failed\n");
		char proInfo[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
		cout<<proInfo<<"\n";
	}
	char proInfo[512];
	glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
	cout<<proInfo<<"\n";

	// ================ Program - 2 - Setup ====================//


	//==============Triangle- 1 - Buffer setup=================//
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    // Create a Vertex Buffer Object and copy the vertex data to it
    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float vertices[] = {
         0.0f,  0.5f, 1.0f, 0.0f, 0.0f,  // Vertex 1: Red
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f,  // Vertex 2: Green
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f   // Vertex 3: Blue
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Getting positions from buffer into the program
	GLuint posLoc = glGetAttribLocation(shaderProgram, "p");
	printf("%i\n", posLoc);
	glVertexAttribPointer(posLoc, 2, GL_FLOAT,GL_FALSE,5*sizeof(float) , 0);

	glEnableVertexAttribArray(posLoc);
	GLenum err;

	GLuint color = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));

	glBindVertexArray(0);

	//==============Triangle- 2 - Buffer setup=================//
	GLuint vao2, vbo2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	float vertices2[] = {
		1.0f, 0.5f, 1.0f, 1.0f, 0.0f,
		0.5f, 1.0f, 0.5f, 0.5f, 0.5f,
		0.5f, 0.0f, 0.0f, 1.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(posLoc);

	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(color);


	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
		cout << gluErrorString(err) << "\n";
    }
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
		cout << gluErrorString(err) << "\n";
    }
	while(!glfwWindowShouldClose(window)){
		// glClearColor(1.0f,0.5f, 0.5f, 1.0f);
		// glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(vao2);
		glUseProgram(shaderProgram);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		while ((err = glGetError()) != GL_NO_ERROR) {
			cout << "OpenGL error: " << err << "\n";
			cout << gluErrorString(err) << "\n";
    	}
        glfwSwapBuffers(window);
    	glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
