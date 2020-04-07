/**
 *  Helpers for creating shaders
 */ 
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<GL/glew.h>

using std::cout;
using std::ifstream;
using std::string;
using std::getline;

string reader(){
    ifstream infile;
    infile.open("./file.txt", std::ios::in);
    if(!infile.is_open()){
	    printf("Failed to read shader");
    }
    std::stringstream buffer;
    buffer<<infile.rdbuf();
    buffer<<"\0";
    infile.close();
    return buffer.str();
    //string line;
    //string finalLine;
    //while(getline(infile, line)){
      //  finalLine += line;
    //}
    //infile.close();
    //const char* rLine = finalLine.c_str();
    //return finalLine;
}

string reader(char* file){
    ifstream infile;
    infile.open(file, std::ios::in);
    if(!infile.is_open()){
	    printf("Failed to read shader\n");
      printf("%s\n", file);
    }
    std::stringstream buffer;
    buffer<<infile.rdbuf();
    infile.close();
    printf(buffer.str().c_str());
    string sha = buffer.str();
    return sha;
}

void createShader(char* sourceFile, GLuint shader){
  string p = reader(sourceFile);
  const char* source = p.c_str();
	printf("%s\n", source);
	glShaderSource(shader, 1, &source, 0);
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

//TODO:Removed to make it a library
// int main(){
//     cout<<reader();
//     return 0;
// }
