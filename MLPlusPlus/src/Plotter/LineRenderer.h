#pragma once

#include <glm/glm.hpp>

#define MAX_LINES			10
#define LINE_VERTEX_SIZE	sizeof(LineData)
#define LINES_SIZE			LINE_VERTEX_SIZE * 1
#define LINES_BUFFER_SIZE	LINES_SIZE * MAX_LINES

struct LineData
{
	float x, y;
	glm::vec4 colour;
};

class LineRenderer
{
private:
	unsigned int VBO, IBO, VAO;
	int indexCount;
	LineData* lineData;
	class Shader* shader;
public:
	LineRenderer(class Shader* shader);
	~LineRenderer();

	void begin();
	void submit(double x0, double y0, double x1, double y1, glm::vec4 colour);
	void draw(class Window* window, float delta);
	void end();
};