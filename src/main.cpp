#include<GL/glew.h>
#include<stdio.h>
#include<hello.h>
#include<glfw3.h>

void error_callback(int error, const char* description)
{
    printf("Error: %s\n", description);
    char* raw = "Aashay";
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
	glfwSwapBuffers(window);


	GLuint *vertexBuffer = new GLuint[2];
	printf("%p\n",glGenBuffers);
	glGenBuffers(1,vertexBuffer);

	printf("%p\n", vertexBuffer);


	while(!glfwWindowShouldClose(window)){
		glfwSwapBuffers(window);
    		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
