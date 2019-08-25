#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Plane.h"

class Plane;

class Line
{
public:
	Vector3D	direction;
	Vector3D	moment;

	Line() = default;

	Line(float vx, float vy, float vz, float mx, float my, float mz) :
		direction(vx, vy, vz), moment(mx, my, mz)
	{
	}

	Line(const Vector3D& v, const Vector3D& m)
	{
		direction = v;
		moment = m;
	}
};


extern Line Transform(const Line& line, const Transform4D& H);
extern inline Line operator ^(const Point3D& p, const Point3D& q);
extern inline Line operator ^(const Plane& f, const Plane& g);
