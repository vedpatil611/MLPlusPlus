#pragma once

#include <glm/glm.hpp>
#include <unordered_map>

class Shader
{
private:
	unsigned int m_ShaderID;
	std::unordered_map<const char*, int> m_UniformLocationCache;
public:
	Shader(const char* vertPath, const char* fragPath);
	~Shader();

	void setUniform1i(const char* uniformName, int value);
	void setUniform1f(const char* uniformName, float value);
	void setUniformMat4(const char* uniformName, const glm::mat4& mat);

	void bind() const;
	void unbind() const;
private:
	unsigned int compileShader(unsigned int type, const char* src);
	unsigned int createShaderProgram(const char* vertexShader, const char* fragmentShader);

	int getUniformLocation(const char* uniformName);
};