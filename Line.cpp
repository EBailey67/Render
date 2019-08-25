#include "Matrix.h"
#include "Line.h"

Line Transform(const Line& line, const Transform4D& H)
{
	Matrix3D adj(Cross(H[1], H[2]), Cross(H[2], H[0]), Cross(H[0], H[1]));
	const Point3D& t = H.GetTranslation();

	Vector3D v = H * line.direction;
	Vector3D m = adj * line.moment + Cross(t, v);
	return (Line(v, m));
}

inline Line operator ^(const Point3D& p, const Point3D& q)
{
	return (Line(q.x - p.x, q.y - p.y, q.z - p.z,
		p.y * q.z - p.z * q.y, p.z * q.x - p.x * q.z, p.x * q.y - p.y * q.x));
}

inline Line operator ^(const Plane& f, const Plane& g)
{
	return (Line(f.y * g.z - f.z * g.y,
		f.z * g.x - f.x * g.z,
		f.x * g.y - f.y * g.x,
		g.x * f.w - f.x * g.w,
		g.y * f.w - f.y * g.w,
		g.z * f.w - f.z * g.w));
}
