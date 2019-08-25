#pragma once

#include <math.h>

static constexpr float FLT_MIN = 0.00001f;

struct Vector3D
{
	float		x, y, z;

	Vector3D() = default;

	Vector3D(float a, float b, float c)
	{
		x = a;
		y = b;
		z = c;
	}

	float& operator [](int i)
	{
		return ((&x)[i]);
	}

	const float& operator [](int i) const
	{
		return ((&x)[i]);
	}

	Vector3D& operator *=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}

	Vector3D& operator /=(float s)
	{
		s = 1.0F / s;
		x *= s;
		y *= s;
		z *= s;
		return (*this);
	}

	Vector3D& operator +=(const Vector3D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return (*this);
	}

	Vector3D& operator -=(const Vector3D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return (*this);
	}
};

// 4D version
struct Vector4D
{
	float		x, y, z, w;

	Vector4D() = default;

	Vector4D(float a, float b, float c, float d)
	{
		x = a;
		y = b;
		z = c;
		w = d;
	}

	float& operator [](int i)
	{
		return ((&x)[i]);
	}

	const float& operator [](int i) const
	{
		return ((&x)[i]);
	}

	Vector4D& operator *=(float s)
	{
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return (*this);
	}

	Vector4D& operator /=(float s)
	{
		s = 1.0F / s;
		x *= s;
		y *= s;
		z *= s;
		w *= s;
		return (*this);
	}

	Vector4D& operator +=(const Vector4D& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return (*this);
	}

	Vector4D& operator -=(const Vector4D& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return (*this);
	}
};

extern inline Vector3D operator *(const Vector3D& v, float s);
extern inline Vector3D operator /(const Vector3D& v, float s);
extern inline Vector3D operator -(const Vector3D& v);
extern inline float Magnitude(const Vector3D& v);
extern inline Vector3D Normalize(const Vector3D& v);
extern inline Vector3D operator +(const Vector3D& a, const Vector3D& b);
extern inline Vector3D operator -(const Vector3D& a, const Vector3D& b);
extern inline float Dot(const Vector3D& a, const Vector3D& b);
extern inline Vector3D Cross(const Vector3D& a, const Vector3D& b);
extern inline Vector3D Project(const Vector3D& a, const Vector3D& b);
extern inline Vector3D Reject(const Vector3D& a, const Vector3D& b);


struct Point3D : Vector3D
{
	Point3D() = default;

	Point3D(float a, float b, float c) : Vector3D(a, b, c) {}

	Point3D& operator =(const Vector3D& v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		return (*this);
	}
};

inline Point3D operator +(const Point3D& a, const Vector3D& b)
{
	return (Point3D(a.x + b.x, a.y + b.y, a.z + b.z));
}

inline Point3D operator -(const Point3D& a, const Vector3D& b)
{
	return (Point3D(a.x - b.x, a.y - b.y, a.z - b.z));
}

inline Vector3D operator -(const Point3D& a, const Point3D& b)
{
	return (Vector3D(a.x - b.x, a.y - b.y, a.z - b.z));
}

extern float DistPointLine(const Point3D& q, const Point3D& p, const Vector3D& v);
extern float DistLineLine(const Point3D& p1, const Vector3D& v1,
	const Point3D& p2, const Vector3D& v2);

