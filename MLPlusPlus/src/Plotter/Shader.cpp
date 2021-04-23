#include "Shader.h"

#include <glad/glad.h>
#include <Utils/File.h>

Shader::Shader(const char* vertPath, const char* fragPath)
{
	const char* vertSrc = Utils::readFile(vertPath);
	const char* fragSrc = Utils::readFile(fragPath);
	m_ShaderID = createShaderProgram(vertSrc, fragSrc);
}

Shader::~Shader()
{
	glDeleteProgram(m_ShaderID);
}

void Shader::setUniform1i(const char* uniformName, int value)
{
	glUniform1i(getUniformLocation(uniformName), value);
}

void Shader::setUniform1f(const char* uniformName, float value)
{
	glUniform1f(getUniformLocation(uniformName), value);
}

void Shader::setUniformMat4(const char* uniformName, const glm::mat4& mat)
{
	glUniformMatrix4fv(getUniformLocation(uniformName), 1, false, &mat[0][0]);
}

void Shader::bind() const
{
	glUseProgram(m_ShaderID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

unsigned int Shader::compileShader(unsigned int type, const char* src)
{
	unsigned int id = glCreateShader(type);
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

#ifdef DEBUG
	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		printf("Failed to compile %s shader: %s\n", (type == GL_VERTEX_SHADER ? "vertex" : "fragment"), message);
		glDeleteShader(id);
		delete[] message;
		return 0;
	}
#endif // DEBUG

	return id;
}

unsigned int Shader::createShaderProgram(const char* vertexShader, const char* fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = compileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned int fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

int Shader::getUniformLocation(const char* uniformName)
{
	if (m_UniformLocationCache.find(uniformName) != m_UniformLocationCache.end())
		return m_UniformLocationCache[uniformName];

	int location = glGetUniformLocation(m_ShaderID, uniformName);
	if (location == -1)
		printf("\033[1;33m Warning: uniform %s not found\n\033[0;39m", uniformName);

	return location;
}
