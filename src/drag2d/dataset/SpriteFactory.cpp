/*
* Copyright (c) 2012-2013 XZRUNNER http://runnersoft.net
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

#include "SpriteFactory.h"
#include "ImageSprite.h"
#include "ShapeSprite.h"
#include "MeshSprite.h"
#include "CombinationSprite.h"

using namespace d2d;

ISprite* SpriteFactory::create(ISymbol* symbol)
{
	ImageSymbol* image = dynamic_cast<ImageSymbol*>(symbol);
	if (image) return new ImageSprite(image);

	ShapeSymbol* shape = dynamic_cast<ShapeSymbol*>(symbol);
	if (shape) return new ShapeSprite(shape);

	MeshSymbol* mesh = dynamic_cast<MeshSymbol*>(symbol);
	if (mesh) return new MeshSprite(mesh);

	CombinationSymbol* combination = dynamic_cast<CombinationSymbol*>(symbol);
	if (combination) return new CombinationSprite(combination);

	return NULL;
}
