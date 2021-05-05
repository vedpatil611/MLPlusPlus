#pragma once

#include <glm/glm.hpp>
#include <Plotter/Points.h>
#include <vector>

#define MAX_POINTS			1000
#define POINT_VERTEX_SIZE	sizeof(PointData)
#define POINTS_SIZE			POINT_VERTEX_SIZE * 2
#define POINTS_BUFFER_SIZE	POINTS_SIZE * MAX_POINTS

#define VERTEX_OFFSET(offset) (const void*) ((offset) * sizeof(float))

class PointRenderer
{
private:
	unsigned int VBO, IBO, VAO;
	int indexCount;
	PointData* pointData;
	class Shader* shader;
public:
	PointRenderer(class Shader* shader);
	~PointRenderer();

	void begin();
	void submit(double x, double y, glm::vec4 colour);
	void draw(class Window* window, float delta);
	void end();
};