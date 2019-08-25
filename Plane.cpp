#include "Plane.h"

float Dot(const Plane& f, const Vector3D& v)
{
	return (f.x * v.x + f.y * v.y + f.z * v.z);
}

float Dot(const Plane& f, const Point3D& p)
{
	return (f.x * p.x + f.y * p.y + f.z * p.z + f.w);
}

Transform4D MakeReflection(const Plane& f)
{
	float x = f.x * -2.0F;
	float y = f.y * -2.0F;
	float z = f.z * -2.0F;
	float nxny = x * f.y;
	float nxnz = x * f.z;
	float nynz = y * f.z;

	return (Transform4D(x * f.x + 1.0F, nxny, nxnz, x * f.w,
		nxny, y * f.y + 1.0F, nynz, y * f.w,
		nxnz, nynz, z * f.z + 1.0F, z * f.w));
}

float IntersectLinePlane(const Point3D& p, const Vector3D& v,
	const Plane& f, Point3D* q)
{
	float fv = Dot(f, v);
	if (fabs(fv) > FLT_MIN)
	{
		*q = p - v * (Dot(f, p) / fv);
		return (true);
	}

	return (false);
}


bool IntersectThreePlanes(const Plane& f1, const Plane& f2,
	const Plane& f3, Point3D* p)
{
	const Vector3D& n1 = f1.GetNormal();
	const Vector3D& n2 = f2.GetNormal();
	const Vector3D& n3 = f3.GetNormal();

	Vector3D n1xn2 = Cross(n1, n2);
	float det = Dot(n1xn2, n3);
	if (fabs(det) > FLT_MIN)
	{
		*p = (Cross(n3, n2) * f1.w + Cross(n1, n3) * f2.w
			- n1xn2 * f3.w) / det;
		return (true);
	}

	return (false);
}


bool IntersectTwoPlanes(const Plane& f1, const Plane& f2,
	Point3D* p, Vector3D* v)
{
	const Vector3D& n1 = f1.GetNormal();
	const Vector3D& n2 = f2.GetNormal();

	*v = Cross(n1, n2);
	float det = Dot(*v, *v);
	if (fabs(det) > FLT_MIN)
	{
		*p = (Cross(*v, n2) * f1.w + Cross(n1, *v) * f2.w) / det;
		return (true);
	}

	return (false);
}


Plane operator *(const Plane& f, const Transform4D& H)
{
	return (Plane(f.x * H(0, 0) + f.y * H(1, 0) + f.z * H(2, 0),
		f.x * H(0, 1) + f.y * H(1, 1) + f.z * H(2, 1),
		f.x * H(0, 2) + f.y * H(1, 2) + f.z * H(2, 2),
		f.x * H(0, 3) + f.y * H(1, 3) + f.z * H(2, 3) + f.w));
}


inline Plane operator ^(const Line& L, const Point3D& p)
{
	return (Plane(L.direction.y * p.z - L.direction.z * p.y + L.moment.x,
		L.direction.z * p.x - L.direction.x * p.z + L.moment.y,
		L.direction.x * p.y - L.direction.y * p.x + L.moment.z,
		-L.moment.x * p.x - L.moment.y * p.y - L.moment.z * p.z));
}

inline Plane operator ^(const Point3D& p, const Line& L)
{
	return (L ^ p);
}

inline Vector4D operator ^(const Line& L, const Plane& f)
{
	return (Vector4D(
		L.moment.y * f.z - L.moment.z * f.y + L.direction.x * f.w,
		L.moment.z * f.x - L.moment.x * f.z + L.direction.y * f.w,
		L.moment.x * f.y - L.moment.y * f.x + L.direction.z * f.w,
		-L.direction.x * f.x - L.direction.y * f.y - L.direction.z * f.z));
}

inline Vector4D operator ^(const Plane& f, const Line& L)
{
	return (L ^ f);
}

inline float operator ^(const Line& L1, const Line& L2)
{
	return (-(Dot(L1.direction, L2.moment) + Dot(L2.direction, L1.moment)));
}

inline float operator ^(const Point3D& p, const Plane& f)
{
	return (p.x * f.x + p.y * f.y + p.z * f.z + f.w);
}

inline float operator ^(const Plane& f, const Point3D& p)
{
	return (-(p ^ f));
}
