#pragma once

#include "libs/glew/include/GL/glew.h"
#include "libs/glfw/include/GLFW/glfw3.h"
#include "libs/glm/glm/glm.hpp"
#include "libs/glm/glm/gtc/type_ptr.hpp"
#include <string>

// Utitlity class to load, compile and attach a vertex- and fragment shader to a program
class ShaderUtil
{

private: 
	unsigned int mProgramId;

	unsigned int GetCompiledShader(unsigned int shader_type, const std::string& shader_source);

public:
	ShaderUtil() {}
	~ShaderUtil() {}

	// Load a vertex and a fragment shader from file
	bool Load(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

	// Use the program
	void Use();

	// Delete the program
	void Delete();

	void SetMat4(const std::string& name, glm::mat4 val);

};

