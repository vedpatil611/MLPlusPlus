#include "LineRenderer.h"

#include <Window.h>
#include <glad/glad.h>
#include <Plotter/Shader.h>

#define VERTEX_OFFSET(offset) (const void*) ((offset) * sizeof(float))

LineRenderer::LineRenderer(Shader* shader)
	:shader(shader)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, LINES_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, LINE_VERTEX_SIZE, VERTEX_OFFSET(0));
	glVertexAttribPointer(1, 4, GL_FLOAT, false, LINE_VERTEX_SIZE, VERTEX_OFFSET(2));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned short indices[MAX_LINES * 2];

	for (int i = 0; i < MAX_LINES * 2; ++i)
	{
		indices[i] = i;
	}

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_LINES * 2, indices, GL_STATIC_DRAW);
}

LineRenderer::~LineRenderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void LineRenderer::begin()
{
	indexCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	lineData = (LineData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void LineRenderer::submit(double x0, double y0, double x1, double y1, glm::vec4 colour)
{
	lineData->x = static_cast<float>(x0);
	lineData->y = static_cast<float>(y0);
	lineData->colour = colour;
	++lineData;

	lineData->x = static_cast<float>(x1);
	lineData->y = static_cast<float>(y1);
	lineData->colour = colour;
	++lineData;

	indexCount += 2;
}

void LineRenderer::draw(Window* window, float delta)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	shader->bind();
	shader->setUniformMat4("uProj", window->getProjMatrix());

	glDrawElements(GL_LINES, indexCount, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LineRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
