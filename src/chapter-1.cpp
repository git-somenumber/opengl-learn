#include<GL/glew.h>
#include<glfw3.h>
#include<stdio.h>
#include"shader.cpp"
#include<math.h>
#include<glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using std::cout;
using std::ifstream;
using std::string;
using std::getline;

void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
}

void key_callback(GLFWwindow* window, int a, int b, int c, int d)
{
	glfwSetWindowShouldClose(window, GLFW_TRUE);
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
	glfwWindowHint(GLFW_FOCUSED, GLFW_FALSE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "One", NULL, NULL);
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
	glfwSetKeyCallback(window, key_callback);

	int width, height;
    	glfwGetFramebufferSize(window, &width, &height);  
    	glViewport(0, 0, width, height);

	// ================= Shaders for program - 1 ============== //
	// Vertex Shader 1
	GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
	createShader((char*)"./shaders/chapter-one.vert", vShader);
	// Fragment Shader 1
	GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
	createShader((char*)"./shaders/chapter-one.frag", fShader);

	// ================= Shaders for program - 1 ============== //

	GLuint fShader2 = glCreateShader(GL_FRAGMENT_SHADER);
	createShader((char*)"./shaders/one-uniform.frag", fShader2);	


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

	// ================ Program - 2 - Setup ==================== //
	GLuint shaderProgram2 = glCreateProgram();
	glAttachShader(shaderProgram2, vShader);
	glAttachShader(shaderProgram2, fShader2);
	glLinkProgram(shaderProgram2);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &proStatus);
	if(proStatus!=GL_TRUE){
		printf("Linking failed\n");
		char proInfo[512];
		glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
		cout<<proInfo<<"\n";
	}
	glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
	cout<<proInfo<<"\n";


	//==============Triangle- 1 - Buffer setup=================//
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	// Create a Vertex Buffer Object and copy the vertex data to it
	GLuint vbo, ebo;
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	float indices[] = {
		0,1,2,
		1,2,3
	};
    float vertices[] = {
         0.5f,  0.5f,0.0f,    1.0f, 0.0f, 0.0f,  // Vertex 1: Red
         0.5f, -0.5f,0.0f,    0.0f, 1.0f, 0.0f,  // Vertex 2: Green
        -0.5f, -0.5f,0.0f,    0.0f, 0.0f, 1.0f,  // Vertex 3: Blue
		-0.5f,  0.5f,0.0f,    0.0f, 0.0f, 1.0f
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Getting positions from buffer into the program
	GLuint posLoc = glGetAttribLocation(shaderProgram, "p");
	glVertexAttribPointer(posLoc, 3, GL_FLOAT,GL_FALSE,6*sizeof(float) , 0);

	glEnableVertexAttribArray(posLoc);
	GLenum err;

	GLuint color = glGetAttribLocation(shaderProgram, "color");
	glEnableVertexAttribArray(color);
	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 6*sizeof(float), (void*)(3*sizeof(float)));

	glBindVertexArray(0);

	//==============Triangle- 2 - Buffer setup=================//
	GLuint vao2, vbo2;
	glGenVertexArrays(1, &vao2);
	glBindVertexArray(vao2);
	glGenBuffers(1, &vbo2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);

	float vertices2[] = {
		1.0f, 0.5f,    1.0f, 1.0f, 0.0f,
		0.5f, 1.0f,    0.5f, 0.5f, 0.5f,
		0.5f, 0.0f,    0.0f, 1.0f, 1.0f
	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 0);
	glEnableVertexAttribArray(posLoc);

	glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(color);

	// Using the uniform
	GLint uniLoc = glGetUniformLocation(shaderProgram2, "triangleCol");


	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
		cout << gluErrorString(err) << "\n";
    }
	glUseProgram(shaderProgram);
	glBindVertexArray(vao);

	// ================== Setting up matrices ================== //
	glm::mat4 modelMat = glm::mat4(1.0f);
	modelMat = glm::rotate(modelMat, glm::radians(-45.0f), glm::vec3(1.0f,0.0f,0.0f));

	glm::mat4 viewMat = glm::mat4(1.0f);
	viewMat = glm::translate(viewMat, glm::vec3(0.0f,0.0f, -1.0f));
	// viewMat = glm::lookAt(
	// 	glm::vec3(0.0f, 0.0f, -1.0f),
    //  	glm::vec3(0.0f, 0.0f, 0.0f),
    // 	glm::vec3(0.0f, 1.0f, 0.0f)
	// );

	glm::mat4 projMat = glm::mat4(1.0f);
	projMat = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f,100.0f);
	printf("%f,%f, %f,%f \n", projMat[0].x, projMat[0].y, projMat[0].z, projMat[0].w);
	printf("%f,%f, %f,%f \n", projMat[1].x, projMat[1].y, projMat[1].z, projMat[1].w);
	printf("%f,%f, %f,%f \n", projMat[2].x, projMat[2].y, projMat[2].z, projMat[2].w);
	printf("%f,%f, %f,%f \n", projMat[3].x, projMat[3].y, projMat[3].z, projMat[3].w);

	// ================== Looking up matrix location ================== //
	GLint model = glGetUniformLocation(shaderProgram, "model");
	GLint view = glGetUniformLocation(shaderProgram, "view");
	GLint proj  = glGetUniformLocation(shaderProgram, "proj");
	cout<< "model: " << model 
		<< "\n view: "<< view 
		<< "\n proj: " << proj << "\n";
	
	while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
		cout << gluErrorString(err) << "\n";
    }
	while(!glfwWindowShouldClose(window)){
		glClearColor(1.0f,0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		double time = glfwGetTime();
		GLfloat sine = sin(time/200);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao);
		
		modelMat =  glm::rotate(modelMat, glm::radians(sine*180.0f), glm::vec3(1.0f,0.0f,0.0f));
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
		// viewMat = glm::lookAt(
		// glm::vec3(0.0f, 0.0f, 1.0f),
     	// glm::vec3(0.5f, 0.5f, 0.0f),
    	// glm::vec3(0.0f, 1.0f, 0.0f)
		// );
		glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));
		glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(projMat));
		glDrawArrays(GL_TRIANGLES, 0,3);
		modelMat =  glm::rotate(modelMat, glm::radians(5.0f), glm::vec3(1.0f,0.0f,0.0f));
		glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
		glDrawArrays(GL_TRIANGLES, 1,3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		// No error
		glBindVertexArray(vao2);
		glUseProgram(shaderProgram2);
		glUniform3f(uniLoc, 0.4f, 0.3f, 0.7f);
		GLint model2= glGetUniformLocation(shaderProgram2, "model");
		glUniformMatrix4fv(model2, 1,GL_FALSE, glm::value_ptr(modelMat));
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
