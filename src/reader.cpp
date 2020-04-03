#include<stdio.h>
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>

using std::cout;
using std::ifstream;
using std::string;
using std::getline;

string reader(){
    ifstream infile;
    infile.open("./file.txt", std::ios::in);
    string line;
    string finalLine;
    while(getline(infile, line)){
        finalLine += line;
    }
    infile.close();
    const char* rLine = finalLine.c_str();
    return finalLine;
}

string reader(const char* file){
    ifstream infile;
    infile.open(file, std::ios::in);
    string line;
    string finalLine;
    while(getline(infile, line)){
        finalLine += line;
		finalLine += "\n";
    }
    infile.close();
	return finalLine;
}

// void reader(){
//     std::ifstream shader;
//     std::string line;
//     char* myline;

//     shader.open("./file.txt", std::ios::in);
//     if(shader.is_open()){
//         shader>>myline;
//         std::cout<<myline<<"\n";
//     }
//     else{
//         printf("Failed to open file");
//     }
// }

//TODO:Removed to make it a library
// int main(){
//     cout<<reader();
//     return 0;
// }