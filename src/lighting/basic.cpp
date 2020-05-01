#include <stdio.h>
#include <shader.cpp>
#include <GL/glew.h>
#include <glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

void glfw_call(GLFWwindow * window, int a , int b, int c, int d)
{
    if(a == GLFW_KEY_Q){
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

using std::vector;
struct program
{
    GLuint vShader;
    GLuint fShader;
    GLuint program;
    char* vSource;
    char* fSource;
    vector<char*> attr;
    vector<GLuint> attrLoc;
};
void programInit(program &p)
{
    p.vShader = glCreateShader(GL_VERTEX_SHADER);
    p.fShader = glCreateShader(GL_FRAGMENT_SHADER);
    createShader(p.vSource, p.vShader);
    createShader(p.fSource, p.fShader);

    p.program = glCreateProgram();
    glAttachShader(p.program, p.vShader);
    glAttachShader(p.program, p.fShader);
    glLinkProgram(p.program);
    GLint proStatus;
    glGetProgramiv(p.program, GL_LINK_STATUS, &proStatus);
    if(proStatus!=GL_TRUE)
    {
	printf("Linking failed\n");
    }
    char proInfo[512];
    glGetProgramInfoLog(p.program, 512, NULL, proInfo);
    std::cout<<proInfo<<"\n";
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
	GLFWwindow* window = glfwCreateWindow(640, 480, "Lighting-basic", NULL, NULL);
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

    program p1;
    p1.fSource = "./shaders/light/basic.frag";
    p1.vSource = "./shaders/light/basic.vert";
    programInit(p1);
    p1.attr.push_back("color");
    // Locations of attributes
    GLint posLoc = glGetAttribLocation(p1.program, "pos");
    GLint colLoc = glGetAttribLocation(p1.program, "color");
    GLint model = glGetUniformLocation(p1.program, "model");
    GLint view = glGetUniformLocation(p1.program, "view");
    GLint proj = glGetUniformLocation(p1.program, "proj");

GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{one-3}"<< "\n";
    }
    GLuint vao, vbo, ebo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

GLfloat verticesCube[] = {
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
     0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f,
     0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f
};
    glBufferData(GL_ARRAY_BUFFER, sizeof(verticesCube), verticesCube, GL_STATIC_DRAW);

    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << posLoc << "  {y0}"<< "\n";
    }
    glEnableVertexAttribArray(posLoc);
    glVertexAttribPointer(posLoc, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

    glEnableVertexAttribArray(colLoc);
    glVertexAttribPointer(colLoc, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));

    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{one-1}"<< "\n";
    }
    glm::mat4 modelMat = glm::mat4(1.0f);
    modelMat = glm::rotate(modelMat, glm::radians(45.0f), glm::vec3(1.0f, 0.0f, 1.0f));
    glm::mat4 viewMat = glm::mat4(1.0f);
    viewMat = glm::translate(viewMat, glm::vec3(0.0f, 0.0f,-3.0f));
    glm::mat4 projMat = glm::mat4(1.0f);
    projMat = glm::perspective(glm::radians(45.0f), 640.0f/480.0f, 0.01f,100.0f);

    while ((err = glGetError()) != GL_NO_ERROR) {
	    std::cout << "OpenGL error: " << err << "\n";
	    cout << gluErrorString(err) << "{one-2}"<< "\n";
    }
    glUseProgram(p1.program);
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));
    glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(projMat));
    cout<< model<<":Model"<<view<<":view"<<proj<<"proj\n";

    while ((err = glGetError()) != GL_NO_ERROR) {
	    std::cout << "OpenGL error: " << err << "\n";
	    cout << gluErrorString(err) << "{two}"<< "\n";
    }
    while(!glfwWindowShouldClose(window)){
        glEnable(GL_DEPTH_TEST);
        // glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(p1.program);
        glBindVertexArray(vao);
        glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
        glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMat));
        glUniformMatrix4fv(proj, 1, GL_FALSE, glm::value_ptr(projMat));
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glDisable(GL_DEPTH_TEST);
    }
    while ((err = glGetError()) != GL_NO_ERROR) {
	std::cout << "OpenGL error: " << err << "\n";
	cout << gluErrorString(err) << "{end}"<< "\n";
    }
    glfwDestroyWindow(window);
    glfwTerminate();
}
