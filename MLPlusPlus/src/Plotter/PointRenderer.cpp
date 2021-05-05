#include "PointRenderer.h"

#include <glad/glad.h>
#include <Plotter/Shader.h>
#include <Window.h>

PointRenderer::PointRenderer(Shader* shader)
	:shader(shader)
{
	glGenBuffers(1, &VBO);
	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, POINTS_BUFFER_SIZE, nullptr, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, false, POINT_VERTEX_SIZE, VERTEX_OFFSET(0));
	glVertexAttribPointer(1, 4, GL_FLOAT, false, POINT_VERTEX_SIZE, VERTEX_OFFSET(2));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned short indices[MAX_POINTS];

	for (int i = 0; i < MAX_POINTS; ++i)
	{
		indices[i] = i;
	}

	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_POINTS, indices, GL_STATIC_DRAW);
}

PointRenderer::~PointRenderer()
{
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &IBO);
	glDeleteVertexArrays(1, &VAO);
}

void PointRenderer::begin()
{
	indexCount = 0;
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	pointData = (PointData*) glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void PointRenderer::submit(double x, double y, glm::vec4 colour)
{
	pointData->x = static_cast<float>(x);
	pointData->y = static_cast<float>(y);
	pointData->colour = colour;
	++pointData;
	
	++indexCount;
}

void PointRenderer::draw(Window* window, float delta)
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	shader->bind();
	shader->setUniformMat4("uProj", window->getProjMatrix());

	glDrawElements(GL_POINTS, indexCount, GL_UNSIGNED_SHORT, nullptr);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void PointRenderer::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
}
