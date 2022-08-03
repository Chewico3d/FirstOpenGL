#include "Texture.h"
#include "stb_image.h"

Texture::Texture(const std::string mFilePath)
	:FilePath(mFilePath), LocalBuffer(nullptr), height(0), with(0)
{
	
	stbi_set_flip_vertically_on_load(true);
	LocalBuffer = stbi_load(mFilePath.c_str(), &with, &height, &Bppx,3);

	glGenTextures(1, &Render_Id);
	glBindTexture(GL_TEXTURE_2D, Render_Id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, with, height, 0, GL_RGB, GL_UNSIGNED_BYTE, LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (LocalBuffer)
		stbi_image_free(LocalBuffer);

}

Texture::~Texture()
{
	glDeleteTextures(1, &Render_Id);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, Render_Id);

}

void Texture::UnBind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
