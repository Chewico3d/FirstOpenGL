#pragma once
class VertexBuffer
{
private:
	unsigned int BufferId;
	unsigned int m_Size;
public:
	VertexBuffer(const void*, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;

};

