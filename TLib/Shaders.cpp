#include "Shaders.h"

#include "libs/glew/include/GL/glew.h"
#include <iostream>
#include <fstream>


unsigned int Shaders::GetShader(unsigned int shader_type, const std::string& shader_source)
{
	unsigned int shader_id = glCreateShader(shader_type);
    
	const char* c_source = shader_source.c_str();
	glShaderSource(shader_id, 1, &c_source, nullptr);
	glCompileShader(shader_id);
    
	GLint result;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &length);
        
		GLchar* strInfoLog = new GLchar[length + 1];
		glGetShaderInfoLog(shader_id, length, &length, strInfoLog);
        
		fprintf(stderr, "Compilation error in shader: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
    
	return shader_id;
}

bool Shaders::Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	std::ifstream vsf(vertexShaderFile);
	const std::string vsi((std::istreambuf_iterator<char>(vsf)), std::istreambuf_iterator<char>());
    
	std::ifstream fsf(fragmentShaderFile);
	const std::string fsi((std::istreambuf_iterator<char>(fsf)), std::istreambuf_iterator<char>());
    
	m_PID = glCreateProgram();
    
	unsigned int vs = GetShader(GL_VERTEX_SHADER, vsi);
	unsigned int fs = GetShader(GL_FRAGMENT_SHADER, fsi);
    
	glAttachShader(m_PID, vs);
	glAttachShader(m_PID, fs);
    
	glLinkProgram(m_PID);
	glValidateProgram(m_PID);
    
	glDeleteShader(vs);
	glDeleteShader(fs);
    
	return true;
}

void Shaders::Use()
{
	glUseProgram(m_PID);
}

void Shaders::Delete()
{
	glDeleteProgram(m_PID);
}

