#pragma once

#include <iostream>
#include "libs/glew/include/GL/glew.h"

class Texture
{
    private:
    
	static bool isDefined;
	unsigned int m_rId;
	std::string m_path;
	unsigned char* m_lBuffer;
	int m_width, m_height, m_bpp;
    
    public:
    
	Texture(const std::string& path);
	void loadFromFile(const std::string& path);
    
	~Texture();
    
	void bindTexture(unsigned int slot = 0) const;
	void unbindTexture() const;
    
	int getWidth()
	{
		return m_width;
	}
    
	int getHeight()
	{
		return m_height;
	}
};
