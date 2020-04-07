#include<GL/glew.h>
#include<glfw3.h>
#include"shader.cpp"
// #define STB_IMAGE_IMPLEMENTATION
// #include"stb_image.h"


void glfw_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}


int main()
{
    if(!glfwInit()){
		printf("Error initialising glfw");
	}
	
//	glfwSetErrorCallback(error_callback);
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);

	printf("Running against GLFW %i.%i.%i\n", major, minor, revision);

	// Window creation and hints also check if window creation failed
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Two", NULL, NULL);
    glfwMakeContextCurrent(window);
    if (!window)
	{
    	// Window or OpenGL context creation failed
		printf("Failed to create window");
	}
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
    glfwSetKeyCallback(window, glfw_callback);

    // ================== Shaders ================== //
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    createShader((char*)"./shaders/two.vert", vShader);

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    createShader((char*)"./shaders/two.frag", fShader);

    // ================== Program - 1 ================== //
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(shaderProgram);
    GLint proStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &proStatus);
	if(proStatus!=GL_TRUE)
    {
		printf("Linking failed\n");
	}
	char proInfo[512];
	glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
	cout<<proInfo<<"\n";

    // ================== Setting up Buffer - 1 ================== //
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    
    float vertices[] = 
    {
    // positions          // colors           // texture coords
     0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLuint pos = glGetAttribLocation(shaderProgram, "position");
    printf("%i\n", pos);
    glEnableVertexAttribArray(pos);
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);

    GLuint texCoord = glGetAttribLocation(shaderProgram, "texCoord");
    glEnableVertexAttribArray(texCoord);
    glVertexAttribPointer(texCoord, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(6*sizeof(float)));

    GLuint color = glGetAttribLocation(shaderProgram, "color");
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));


    // ================== Setting up Texture - 1 ================== //
    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    GLint width, height, nrChannels;
    // unsigned char* data = stbi_load("container.jpg", &width, &height, & nrChannels, 0);
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 2, 2, 0, GL_RGB, GL_FLOAT, data);
    // glGenerateMipmap(GL_TEXTURE_2D);
    // stbi_image_free(data);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 4);
    glfwSwapBuffers(window);
    glfwPollEvents();
    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "\n";
        cout << gluErrorString(err) << "\n";
    }


    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 4);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);

	glfwTerminate();
    
}
