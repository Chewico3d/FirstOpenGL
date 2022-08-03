#pragma once

#include "VerexBufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &BufferId);
	glBindVertexArray(BufferId);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &BufferId);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VerexBufferLayout& layout)
{
	vb.Bind();
	const auto& elements = layout.getElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.Type, element.normalized, layout.getStride(), (const void*)offset);	
		offset += element.count * VertexBufferElement::GetSizeOfType(element.Type);

	}
}

void VertexArray::Bind() const
{
	glBindVertexArray(BufferId);
}

void VertexArray::UnBind() const	
{
	glBindVertexArray(0);
}
