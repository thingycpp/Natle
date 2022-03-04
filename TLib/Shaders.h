#pragma once

#include <string>
#include "libs/glew/include/GL/glew.h"
#include "libs/glm/glm/gtc/type_ptr.hpp"
#include "libs/glm/glm/glm.hpp"

class Shaders
{
public:
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	void Use();

	void Delete();

	inline void setVec3(const std::string& name, glm::vec3 vec)
	{
		GLuint id = glGetUniformLocation(m_PID, name.c_str());
		glUniform3fv(id, 1, glm::value_ptr(vec));
	}
	inline void setMat4(const std::string& name, glm::mat4 mat)
	{
		GLuint id = glGetUniformLocation(m_PID, name.c_str());
		glUniformMatrix4fv(id, 1, GL_FALSE, glm::value_ptr(mat));
	}

	inline unsigned int getPID() { return m_PID; }
    
private:
	unsigned int m_PID;
    
	unsigned int GetShader(unsigned int shader_type, const std::string& shader_source);
    
};
