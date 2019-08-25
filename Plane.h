#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "Line.h"

class Line;
class Plane
{
public:
	float x, y, z, w;

	Plane() = default;

	Plane(float nx, float ny, float nz, float d)
	{
		x = nx;
		y = ny;
		z = nz;
		w = d;
	}

	Plane(const Vector3D& n, float d)
	{
		x = n.x;
		y = n.y;
		z = n.z;
		w = d;
	}

	const Vector3D& GetNormal(void) const
	{
		return (reinterpret_cast<const Vector3D&>(x));
	}
};

extern float Dot(const Plane& f, const Vector3D& v);
extern float Dot(const Plane& f, const Point3D& p);
extern Transform4D MakeReflection(const Plane& f);
extern float IntersectLinePlane(const Point3D& p, const Vector3D& v, const Plane& f, Point3D* q);
extern bool IntersectThreePlanes(const Plane& f1, const Plane& f2, const Plane& f3, Point3D* p);
extern bool IntersectTwoPlanes(const Plane& f1, const Plane& f2, Point3D* p, Vector3D* v);
extern Plane operator *(const Plane& f, const Transform4D& H);
extern inline Plane operator ^(const Line& L, const Point3D& p);
extern inline Plane operator ^(const Point3D& p, const Line& L);
extern inline Vector4D operator ^(const Line& L, const Plane& f);
extern inline Vector4D operator ^(const Plane& f, const Line& L);
extern inline float operator ^(const Line& L1, const Line& L2);
extern inline float operator ^(const Point3D& p, const Plane& f);
extern inline float operator ^(const Plane& f, const Point3D& p);
