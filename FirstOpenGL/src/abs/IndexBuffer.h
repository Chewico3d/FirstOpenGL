#pragma once
class IndexBuffer
{
private:
	unsigned int BufferId;
	unsigned int m_count;
public:
	IndexBuffer(const void*, unsigned int size);
	~IndexBuffer();

	void Bind() const;
	void UnBind() const;

	unsigned int GetCount() const { return m_count; }

};

