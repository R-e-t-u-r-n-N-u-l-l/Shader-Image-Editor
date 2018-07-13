#include "shader.h"

using namespace engine;

Shader::Shader(const char* fPath) : m_fPath(fPath) {
	m_shader = load();
	glUseProgram(m_shader);
}

Shader::~Shader() {
	glDeleteProgram(m_shader);
}

GLuint Shader::load() {
	GLuint program  = glCreateProgram();
	GLuint vertex   = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragment = glCreateShader(GL_FRAGMENT_SHADER);

	std::string vSourceRaw = File::loadFileToString("shader.vs");
	std::string fSourceRaw = File::loadFileToString("shader.fs") + File::loadFileToString(m_fPath) + "void main(){run(texture(rawImageSampler, position));}";

	const char* vSource = vSourceRaw.c_str();
	const char* fSource = fSourceRaw.c_str();

	glShaderSource(vertex, 1, &vSource, NULL);
	glCompileShader(vertex);

	if (!checkShader(vertex, "vertex"))
		return 0;

	glShaderSource(fragment, 1, &fSource, NULL);
	glCompileShader(fragment);

	if(!checkShader(fragment, "fragment"))
		return 0;

	glAttachShader(program, vertex);
	glAttachShader(program, fragment);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return program;
}

void Shader::reload(const char* fPath) {
	m_fPath = fPath;
	glDeleteProgram(m_shader);
	m_shader = load();
	glUseProgram(m_shader);
}

bool Shader::checkShader(GLuint& shader, std::string type) {
	GLint status = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE) {
		GLint len;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
		std::vector<char> error(len);
		glGetShaderInfoLog(shader, len, &len, &error[0]);
		std::cout << "Error whilst compiling " << type << " shader: " << std::endl << &error[0] << std::endl;
		glDeleteShader(shader);
		return false;
	}

	return true;
}

GLuint Shader::getUniformLocation(const char* uniformName) {
	GLint location = glGetUniformLocation(m_shader, uniformName);
	return location;
}

void Shader::setUniform1i(GLuint location, int value) {
	glUniform1i(location, value);
}

void Shader::setUniform1f(GLuint location, float value) {
	glUniform1f(location, value);
}

void Shader::setUniform2f(GLuint location, float x, float y) {
	glUniform2f(location, x, y);
}

void Shader::setUniform3f(GLuint location, float x, float y, float z) {
	glUniform3f(location, x, y, z);
}

void Shader::setUniform4f(GLuint location, float x, float y, float z, float w) {
	glUniform4f(location, x, y, z, w);
}