#pragma once

#include "fileio.h"

#include <GL/glew.h>
#include <string>
#include <vector>
#include <iostream>

namespace engine {

	class Shader {

	private:
		GLuint m_shader;
		const char* m_fPath;

		GLuint load();
		bool checkShader(GLuint& shader, std::string type = "");

	public:
		Shader(const char* fPath);
		~Shader();

		void reload(const char* fPath);

		GLuint getUniformLocation(const char* uniformName);

		void setUniform1i(GLuint location, int value);
		void setUniform1f(GLuint location, float value);
		void setUniform2f(GLuint location, float x, float y);
		void setUniform3f(GLuint location, float x, float y, float z);
		void setUniform4f(GLuint location, float x, float y, float z, float w);

	};
}
