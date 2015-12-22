#include "resourceshader.h"
#include <string>
#include <iostream>
#include <fstream>


resourceShader::resourceShader(std::string const &filename) : loaded(0), instances(0)
{
    _filename = filename;
    load(filename);
}

resourceShader::~resourceShader()
{
    glDeleteProgram(program_handle);
    for (std::vector<GLuint>::iterator it = objects.begin(); it != objects.end(); ++it)
        glDeleteShader(*it);

}

void resourceShader::reload()
{

    load(_filename);
}

void resourceShader::bind()
{
    glUseProgram(program_handle);
}


void resourceShader::load(std::string const &filename)
{
    objects.clear();

    std::ifstream input(filename);
    std::string line;
	std::cout << filename << std::endl;


    while( std::getline( input, line ))
    {
		line.erase(line.end()-1, line.end());
		if (!compile(line)) {
			std::cout << "Failed to load shader: " << line << std::endl;
			input.close();
			return;
		}
    }

	input.close();

    if(!link()) return;

    loaded = true;

    std::cout << "Shader loaded succesfuly (" << filename << ")" << std::endl;
}



bool resourceShader::compile(std::string const &filename)
{


    GLuint object_handle;
    if (filename.find(".vert") != std::string::npos)
        object_handle = glCreateShader(GL_VERTEX_SHADER);
    else if (filename.find(".frag") != std::string::npos)
        object_handle = glCreateShader(GL_FRAGMENT_SHADER);
    else if (filename.find(".geom") != std::string::npos)
        object_handle = glCreateShader(GL_GEOMETRY_SHADER);
    else return false;




    std::ifstream in(filename, std::ifstream::in);
	if (!in.is_open())
	{
		std::cout << "Failed to open file: " << filename << std::endl;
		return false;
	}
    std::string shader((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    const char *data = shader.c_str();


    glShaderSource(object_handle, 1, &data, NULL);
    glCompileShader(object_handle);

	in.close();

    GLint Result,InfoLogLength;
    glGetShaderiv(object_handle, GL_COMPILE_STATUS, &Result);

    if (!Result){
        glGetShaderiv(object_handle, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> VertexShaderErrorMessage(InfoLogLength);
        glGetShaderInfoLog(object_handle, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);

        return false;
    }

    objects.push_back(object_handle);

    return true;
}


bool resourceShader::link(){


    program_handle = glCreateProgram();


    for (std::vector<GLuint>::iterator it = objects.begin(); it != objects.end(); ++it)
        glAttachShader(program_handle, *it);

    glLinkProgram(program_handle);

    for (std::vector<GLuint>::iterator it = objects.begin(); it != objects.end(); ++it)
        glDeleteShader(*it);

    GLint Result,InfoLogLength;
    glGetProgramiv(program_handle, GL_LINK_STATUS, &Result);

    if (!Result){
        glGetProgramiv(program_handle, GL_INFO_LOG_LENGTH, &InfoLogLength);
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength);
        glGetProgramInfoLog(program_handle, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);

        return false;
    }

    return true;
}









