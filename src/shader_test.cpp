#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using std::cout;
using std::ifstream;
using std::string;
using std::getline;

string reader(char* file){
    ifstream infile;
    infile.open(file, std::ios::in);

    if(!infile.is_open()){
	    printf("Failed to read shader");
    }
    std::stringstream buffer;
    buffer<<infile.rdbuf();
    buffer<<"\n";
    buffer<<"\0";
    infile.close();
    return buffer.str();
    infile.close();
}


int main()
{
	printf(reader("./shaders/two.vert").c_str());
}
