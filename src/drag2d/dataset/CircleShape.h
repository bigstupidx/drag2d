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

#ifndef D2D_CIRCLE_SHAPE_H
#define D2D_CIRCLE_SHAPE_H

#include "IShape.h"

#include "common/Vector.h"
#include "common/Rect.h"

namespace d2d
{
	class CircleShape : public IShape
	{
	public:
		CircleShape();
		CircleShape(const CircleShape& circle);
		CircleShape(const Vector& center, float radius);

		//
		// IObject interface
		//
		virtual CircleShape* clone();

		//
		// ISerializable interface
		//
		virtual void loadFromTextFile(std::ifstream& fin);
		virtual void storeToTextFile(std::ofstream& fout) const;

		//
		// IShape interface
		//
		virtual bool isContain(const Vector& pos) const;
		virtual bool isIntersect(const Rect& rect) const;
		virtual const Rect& getRect() const { return m_rect; }
		virtual void draw(const Colorf& color = Colorf(0, 0, 0)) const;

	public:
		Vector center;

		float radius;

	private:
		Rect m_rect;

	}; // CircleShape
}

#endif // D2D_CIRCLE_SHAPE_H
