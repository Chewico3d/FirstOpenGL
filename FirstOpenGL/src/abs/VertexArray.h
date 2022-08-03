#pragma once

#include "VertexBuffer.h"

class VertexArray
{
private:
	unsigned int BufferId;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VerexBufferLayout& layout);
	void Bind() const;
	void UnBind() const;

};

