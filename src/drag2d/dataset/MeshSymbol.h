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

#ifndef D2D_MESH_SYMBOL_H
#define D2D_MESH_SYMBOL_H

#include <vector>

#include "ISymbol.h"
#include "Image.h"

#include "common/Vector.h"

namespace d2d
{
	class MeshSymbol : public ISymbol
	{
	public:
		MeshSymbol();
		virtual ~MeshSymbol();

		//
		// IObject interface
		//	
		virtual MeshSymbol* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// ISymbol interface
		//
		virtual void reloadTexture() const;
		virtual void draw(const ISprite* sprite = NULL) const;
		virtual float getWidth(const ISprite* sprite = NULL) const;
		virtual float getHeight(const ISprite* sprite = NULL) const;

		const std::vector<Vector>& getVertices() const;

	private:
		void loadResources();

	private:
		Image* m_image;

		std::vector<Vector> m_vertices;
		std::vector<Vector> m_texCoords;

	}; // MeshSymbol
}

#endif // D2D_MESH_SYMBOL_H
