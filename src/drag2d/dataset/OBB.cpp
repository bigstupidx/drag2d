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

#include "OBB.h"

#include "common/Math.h"

using namespace d2d;

OBB::OBB()
{
	m_angle = 0.0f;
}

OBB::OBB(const OBB& obb)
{
	m_rect = obb.m_rect;
	m_angle = obb.m_angle;
}

OBB* OBB::clone()
{
	return new OBB(*this);
}

void OBB::loadFromTextFile(std::ifstream& fin)
{
	fin >> m_rect.xMin >> m_rect.xMax >> m_rect.yMin >> m_rect.yMax 
		>> m_angle;
}

void OBB::storeToTextFile(std::ofstream& fout) const
{
	fout << m_rect.xMin << " " << m_rect.xMax << " "
		<< m_rect.yMin << " " << m_rect.yMax << '\n'
		<< m_angle << '\n';
}

void OBB::translate(const Vector& offset)
{
	m_rect.translate(offset);
}

void OBB::rotate(float delta)
{
	m_angle += delta;
}

bool OBB::isContain(const Vector& pos) const
{
	const Vector center(m_rect.xCenter(), m_rect.yCenter());
	const Vector trans = Math::rotateVector(pos - center, -m_angle) + center;
	return Math::isPointInRect(trans, m_rect);
}

bool OBB::isIntersect(const Rect& rect) const
{
	// 0 3
	// 1 2
	std::vector<Vector> bound;
	const Vector center(m_rect.xCenter(), m_rect.yCenter());
	Vector trans;
	trans = Math::rotateVector(Vector(m_rect.xMin, m_rect.yMax) - center, m_angle) + center;
	bound.push_back(trans);
	if (Math::isPointInRect(trans, rect)) return true;
	trans = Math::rotateVector(Vector(m_rect.xMin, m_rect.yMin) - center, m_angle) + center;
	bound.push_back(trans);
	if (Math::isPointInRect(trans, rect)) return true;
	trans = Math::rotateVector(Vector(m_rect.xMax, m_rect.yMin) - center,		m_angle) + center;
	bound.push_back(trans);
	if (Math::isPointInRect(trans, rect)) return true;
	trans = Math::rotateVector(Vector(m_rect.xMax, m_rect.yMax) - center, m_angle) + center;
	bound.push_back(trans);
	if (Math::isPointInRect(trans, rect)) return true;

	if (Math::isPointInConvexHull(Vector(rect.xMin, rect.yMin), bound)) return true;
	if (Math::isPointInConvexHull(Vector(rect.xMin, rect.yMax), bound)) return true;
	if (Math::isPointInConvexHull(Vector(rect.xMax, rect.yMin), bound)) return true;
	if (Math::isPointInConvexHull(Vector(rect.xMax, rect.yMax), bound)) return true;

	if (Math::isSegmentIntersectRect(bound[0], bound[1], rect)) return true;
	if (Math::isSegmentIntersectRect(bound[1], bound[2], rect)) return true;
	if (Math::isSegmentIntersectRect(bound[2], bound[3], rect)) return true;
	if (Math::isSegmentIntersectRect(bound[3], bound[0], rect)) return true;

	return false;
}

float OBB::area() const
{
	return m_rect.xLength() * m_rect.yLength();
}

float OBB::width() const
{
	return m_rect.xLength();
}

float OBB::height() const
{
	return m_rect.yLength();
}

Vector OBB::center() const
{
	return Vector(m_rect.xCenter(), m_rect.yCenter());
}

void OBB::getBoundPos(std::vector<Vector>& bound) const
{
	bound.clear();

	const Vector center(m_rect.xCenter(), m_rect.yCenter());
	bound.push_back(Math::rotateVector(Vector(m_rect.xMin, m_rect.yMin) - center, m_angle) + center);
	bound.push_back(Math::rotateVector(Vector(m_rect.xMax, m_rect.yMin) - center, m_angle) + center);
	bound.push_back(Math::rotateVector(Vector(m_rect.xMax, m_rect.yMax) - center, m_angle) + center);
	bound.push_back(Math::rotateVector(Vector(m_rect.xMin, m_rect.yMax) - center, m_angle) + center);
}

Rect OBB::transToRect() const
{
	Vector leftLow(m_rect.xMin, m_rect.yMin),
		rightTop(m_rect.xMax, m_rect.yMax);
	Vector transLeftLow = Math::rotateVector(leftLow, m_angle),
		transRightTop = Math::rotateVector(rightTop, m_angle);

	Rect rect;
	rect.combine(transLeftLow);
	rect.combine(transRightTop);
	return rect;
}
