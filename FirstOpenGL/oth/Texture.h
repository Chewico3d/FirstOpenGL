#pragma once
#include "../src/Renderer.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Texture
{
public:
	unsigned int Render_Id;
	const std::string FilePath;
	unsigned char* LocalBuffer;
	int with, height, Bppx;

	Texture(const std::string FilePath);
	~Texture();

	void Bind(unsigned int slot = 0) const;
	void UnBind();

};

