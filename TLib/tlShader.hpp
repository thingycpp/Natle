#ifndef TLSHADER_H_INCLUDED
#define TLSHADER_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include "libs/glew/include/GL/glew.h"

namespace tl {

	class Shader {

	private:
		static unsigned int m_ProgramID;
		static unsigned int m_ShaderID;

		unsigned int GetCompiledShader(unsigned int shaderType, const std::string& shaderSource);

	public:

		inline unsigned int GetProgram() { return m_ProgramID; }


		void Load(const std::string& vs_filepath, const std::string& fs_filepath);
		void Use();
		void Delete();

	};

}

#endif
