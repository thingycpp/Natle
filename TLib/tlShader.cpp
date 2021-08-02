#include "tlShader.hpp"
using namespace tl;

unsigned int Shader::m_ProgramID = NULL;
unsigned int Shader::m_ShaderID = NULL;

unsigned int Shader::GetCompiledShader(unsigned int shaderType, const std::string& shaderSource) {

	m_ShaderID = glCreateShader(shaderType);
	
	const char* ccp_shaderSource = shaderSource.c_str();
	glShaderSource(m_ShaderID, 1, &ccp_shaderSource, NULL);
	glCompileShader(m_ShaderID);

	GLint no_err;
	glGetShaderiv(m_ShaderID, GL_COMPILE_STATUS, &no_err);

	if (no_err == GL_FALSE) {

		int length;
		glGetShaderiv(m_ShaderID, GL_INFO_LOG_LENGTH, &length);

		GLchar* strInfoLog = new GLchar[length + 1];
		glGetShaderInfoLog(m_ShaderID, length, &length, strInfoLog);

		std::cout << "Error in shader: " << strInfoLog << std::endl;

	}

	return m_ShaderID;

}

void Shader::Load(const std::string& vs_filepath, const std::string& fs_filepath) {

	std::ifstream vs_file(vs_filepath);
	std::string vsf;
	std::string in_vs;
	if (vs_file) {
		
		while (std::getline(vs_file, vsf)) {
			
			in_vs += vsf;

		}

	}
	else {

		std::cout << "Yup... ughm, so.... I could'nt get anything from that file..." << std::endl;

	}

	std::ifstream fs_file(fs_filepath);
	std::string fsf;
	std::string in_fs;
	if (fs_file) {

		while (std::getline(fs_file, fsf)) {

			in_fs += fsf;

		}

	}
	else {

		std::cout << "Yup... ughm, so.... I could'nt get anything from that file either..." << std::endl;

	}

	m_ProgramID = glCreateProgram();

	unsigned int vs = GetCompiledShader(GL_VERTEX_SHADER, in_vs);
	unsigned int fs = GetCompiledShader(GL_FRAGMENT_SHADER, in_fs);

	glAttachShader(m_ProgramID, vs);
	glAttachShader(m_ProgramID, fs);

	glLinkProgram(m_ProgramID);
	glValidateProgram(m_ProgramID);

	glDeleteShader(vs);
	glDeleteShader(fs);

	vs_file.close();
	fs_file.close();

}

void Shader::Use() {

	glUseProgram(m_ProgramID);

}

void Shader::Delete() {

	glDeleteProgram(m_ProgramID);

}