#include<stdio.h>
#include"shader.cpp"
#include<glfw3.h>
#include<GL/glew.h>
#define STB_IMAGE_IMPLEMENTATION
#include<stb_image.h>

void glfw_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	GLFWwindow* window = glfwCreateWindow(640, 480, "Textures", NULL, NULL);
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
    glfwPollEvents();
    glfwSetKeyCallback(window, glfw_callback);

    // Shaders
    GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
    createShader((char*)"shaders/tex-2.vert", vShader);
    char info[512];
	glGetShaderInfoLog(vShader, 512, NULL, info);
	cout << info;

    GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
    createShader((char*)"shaders/tex-2.frag", fShader);
	glGetShaderInfoLog(fShader, 512, NULL, info);
	cout << info;

    GLuint shaderProgram  = glCreateProgram();
    glAttachShader(shaderProgram, vShader);
    glAttachShader(shaderProgram, fShader);
    glLinkProgram(shaderProgram);
    GLint proStatus;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &proStatus);
	if(proStatus!=GL_TRUE){
		printf("Linking failed\n");
	}
	char proInfo[512];
	glGetProgramInfoLog(shaderProgram, 512, NULL, proInfo);
	cout<<proInfo<<"\n";

    // Setting up the texture - container
    GLint width, height, nrChannels;
    unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);
    GLuint tex;
    glGenTextures(1, &tex);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);  
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Pikachu - Texture
    data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);
    GLuint tex2;
    glGenTextures(1, &tex2);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, tex2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);

    // Setting up the buffer
    float vertices[] = 
    {
        // positions          // colors           // texture coords
     0.5f,  0.5f, 0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
     0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
    -0.5f, -0.5f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
    -0.75f,-0.25f,0.0f,   1.0f, 0.123f, 0.32f,0.4f, 0.9f,
    -0.75f,-0.75f,0.0f,   1.0f, 0.123f, 0.32f,0.0f,0.0f,
    -0.25f,-0.5f, 0.0f,   1.0f, 0.123f, 0.32f,-0.8f,-0.3f 
    }; 
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    GLuint pos = glGetAttribLocation(shaderProgram, "pos");
    cout<<pos<<" = pos \n";
    glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), 0);
    glEnableVertexAttribArray(pos);

    GLenum err;
    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "1\n";
		cout << gluErrorString(err) << "\n";
    }    

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float), (void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),(void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << " 2 \n";
		cout << gluErrorString(err) << "\n";
    }

    GLint uni = glGetUniformLocation(shaderProgram, "ourTexture");
    cout<<uni<<" = uni\n";
    glUseProgram(shaderProgram);
    glUniform1i(uni, 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "pikachu"), 1);
    glUniform4f(glGetUniformLocation(shaderProgram, "adj"), 1.0f, 1.0f, 1.0f, 1.0f);

    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << " 3 \n";
		cout << gluErrorString(err) << "\n";
    }

    glUseProgram(shaderProgram);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 4);
    while ((err = glGetError()) != GL_NO_ERROR) {
        cout << "OpenGL error: " << err << "4\n";
		cout << gluErrorString(err) << "\n";
    }

    double val = 0;
    while(!glfwWindowShouldClose(window)){
        float adj = sin(glfwGetTime());
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glUniform4f(glGetUniformLocation(shaderProgram, "adj"), adj+0.5f, adj-0.5, adj, adj);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glDrawArrays(GL_TRIANGLES, 3, 3);
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
