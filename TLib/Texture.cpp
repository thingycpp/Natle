#include "Texture.h"

#include "libs/stb_image/stb_image.h"

bool Texture::isDefined = false;

Texture::Texture(const std::string& path)
:m_path(path), m_rId(0), m_lBuffer(nullptr), m_width(0), m_height(0), m_bpp(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_lBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
    
	glGenTextures(1, &m_rId);
	glBindTexture(GL_TEXTURE_2D, m_rId);
    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);
    
	if (m_lBuffer) {
		stbi_image_free(m_lBuffer);
	}
    
	isDefined = true;
}

void Texture::loadFromFile(const std::string& path)
{
	if (!isDefined) {
		stbi_set_flip_vertically_on_load(1);
		m_lBuffer = stbi_load(path.c_str(), &m_width, &m_height, &m_bpp, 4);
        
		glGenTextures(1, &m_rId);
		glBindTexture(GL_TEXTURE_2D, m_rId);
        
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_lBuffer);
		glBindTexture(GL_TEXTURE_2D, 0);
        
		if (m_lBuffer) {
			stbi_image_free(m_lBuffer);
		}
	}
}

Texture::~Texture()
{
	glDeleteTextures(GL_TEXTURE_2D, &m_rId);
}

void Texture::bindTexture(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_rId);
}

void Texture::unbindTexture() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}