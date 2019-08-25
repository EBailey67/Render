#include <math.h>
#include "Vector.h"
#include "Matrix.h"

inline Vector3D operator *(const Vector3D& v, float s)
{
	return (Vector3D(v.x * s, v.y * s, v.z * s));
}

inline Vector3D operator /(const Vector3D& v, float s)
{
	s = 1.0F / s;
	return (Vector3D(v.x * s, v.y * s, v.z * s));
}

inline Vector3D operator -(const Vector3D& v)
{
	return (Vector3D(-v.x, -v.y, -v.z));
}

inline float Magnitude(const Vector3D& v)
{
	double x = v.x;
	double y = v.y;
	double z = v.z;
	return static_cast<float>(sqrt(x * x + y * y + z * z));
}

inline Vector3D Normalize(const Vector3D& v)
{
	return (v / Magnitude(v));
}

inline Vector3D operator +(const Vector3D& a, const Vector3D& b)
{
	return (Vector3D(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline Vector3D operator -(const Vector3D& a, const Vector3D& b)
{
	return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
}


inline float Dot(const Vector3D& a, const Vector3D& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


inline Vector3D Cross(const Vector3D& a, const Vector3D& b)
{
	return (Vector3D(a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x));
}


inline Vector3D Project(const Vector3D& a, const Vector3D& b)
{
	return (b * (Dot(a, b) / Dot(b, b)));
}

inline Vector3D Reject(const Vector3D& a, const Vector3D& b)
{
	return (a - b * (Dot(a, b) / Dot(b, b)));
}

Vector3D operator *(const Matrix3D& M, const Vector3D& v)
{
	return (Vector3D(M(0, 0) * v.x + M(0, 1) * v.y + M(0, 2) * v.z,
		M(1, 0) * v.x + M(1, 1) * v.y + M(1, 2) * v.z,
		M(2, 0) * v.x + M(2, 1) * v.y + M(2, 2) * v.z));
}

float DistLineLine(const Point3D& p1, const Vector3D& v1,
	const Point3D& p2, const Vector3D& v2)
{
	Vector3D dp = p2 - p1;

	float v12 = Dot(v1, v1);
	float v22 = Dot(v2, v2);
	float v1v2 = Dot(v1, v2);

	float det = v1v2 * v1v2 - v12 * v22;
	if (fabs(det) > FLT_MIN)
	{
		det = 1.0F / det;

		float dpv1 = Dot(dp, v1);
		float dpv2 = Dot(dp, v2);
		float t1 = (v1v2 * dpv2 - v22 * dpv1) * det;
		float t2 = (v12 * dpv2 - v1v2 * dpv1) * det;

		return (Magnitude(dp + v2 * t2 - v1 * t1));
	}

	// The lines are nearly parallel.

	Vector3D a = Cross(dp, v1);
	return static_cast<float>(sqrt(Dot(a, a) / v12));
}

float DistPointLine(const Point3D& q, const Point3D& p, const Vector3D& v)
{
	Vector3D a = Cross(q - p, v);
	return (static_cast<float>(sqrt(Dot(a, a) / Dot(v, v))));
}
