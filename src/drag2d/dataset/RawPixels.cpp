/*
* Copyright (c) 2012-2013 Guang Zhu http://runnersoft.net
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include "RawPixels.h"

#include <SOIL/SOIL.h>

using namespace d2d;

RawPixels::RawPixels()
{
	m_pixelData = NULL;
}

RawPixels::~RawPixels()
{
	SOIL_free_image_data(m_pixelData);
}

void RawPixels::loadFromFile(const char* filepath)
{
	SOIL_free_image_data(m_pixelData);
	m_pixelData = SOIL_load_image(filepath, &m_width, &m_height, &m_channels, 0);
}
// 
// unsigned int RawPixels::storeToTexture(unsigned int old) const
// {
// 	return SOIL_internal_create_OGL_texture(m_pixelData, m_width, m_height, m_channels,
// 		old, SOIL_FLAG_INVERT_Y, GL_TEXTURE_2D, GL_TEXTURE_2D, GL_MAX_TEXTURE_SIZE);
// }

const unsigned char* RawPixels::getPixelData() const
{
	return m_pixelData;
}

void RawPixels::getSize(int& width, int& height) const
{
	width = m_width;
	height = m_height;
}

int RawPixels::getChannels() const
{
	return m_channels;
}

void RawPixels::replaceBySelected(const PixelBuf& selected)
{
	int xStart = m_width, xEnd = 0, 
		yStart = m_height, yEnd = 0;

	PixelBuf::const_iterator itr = selected.begin();
	for ( ; itr != selected.end(); ++itr)
	{
		int x = (*itr)->x,
			y = (*itr)->y;
		if (x < xStart) xStart = x;
		if (x > xEnd) xEnd = x;
		if (y < yStart) yStart = y;
		if (y > yEnd) yEnd = y;
	}

	int tmp = yStart;
	yStart = m_height - 1 - yEnd;
	yEnd = m_height - 1 - tmp;

	int newWidth = xEnd - xStart + 1,
		newHeight = yEnd - yStart + 1;
	unsigned char* newData = (unsigned char*) malloc(newWidth * newHeight * m_channels);
	int index = 0;
 	for (int y = yStart; y <= yEnd; ++y)
 	{
 		for (int x = xStart; x <= xEnd; ++x)
 		{
 			PixelsPos test;
 			test.x = x;
 			test.y = m_height - 1 - y;
 			PixelBuf::const_iterator itr = selected.find(&test);
 			if (itr == selected.end())
 			{
 				newData[index++] = 255;
 				newData[index++] = 255;
 				newData[index++] = 255;
 				if (m_channels == 4) newData[index++] = 0;
 			}
 			else
 			{
 				int base = (m_width * y + x) * m_channels;
 				for (int i = 0; i < m_channels; ++i)
 					newData[index++] = m_pixelData[base + i];
 			}
 		}
 	}

 	SOIL_free_image_data(m_pixelData);
 	m_width = newWidth;
 	m_height = newHeight;
 	m_pixelData = newData;
}
