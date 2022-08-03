#pragma once
#include <iostream> 
#include <vector>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct VertexBufferElement {
	unsigned int Type;
	unsigned int count;
	char normalized;

	static unsigned int GetSizeOfType(unsigned int type) {
		switch (type)
		{
		case GL_FLOAT:
			return 4;
		case GL_UNSIGNED_INT:
			return 4;
		case GL_BYTE:
			return 1;
		}
		return 0;
	}

};

class VerexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Element;
	unsigned int m_Stride;
public:
	VerexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count) {
		
	}

	template <>
	void Push<float>(unsigned int count) {
		m_Element.push_back({ GL_FLOAT, count, false });
		m_Stride += sizeof(float) * count;
	}


	template <>
	void Push<unsigned int >(unsigned	int count) {
		m_Element.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += sizeof(unsigned	int	) * count;
	}

	inline const std::vector<VertexBufferElement> getElements() const { return m_Element; }
	inline const unsigned int getStride() const { return m_Stride; }

};

