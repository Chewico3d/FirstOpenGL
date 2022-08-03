#pragma once
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "abs/VertexBuffer.h"
#include "abs/IndexBuffer.h"
#include "abs/VerexBufferLayout.h"
#include "abs/VertexArray.h"
#include "abs/Shader.h"

class Renderer {
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader);
	void Clear();

};