#pragma once

class VertexBuffer
{
private:
	unsigned int bufferID;
public:
	VertexBuffer(float* data, unsigned count);
	~VertexBuffer();
};