#pragma once

#include "Vector.h"
#include "Matrix.h"


class Quaternion
{
public:
	float		x, y, z, w;

	Quaternion() = default;

	Quaternion(float a, float b, float c, float s)
	{
		x = a; y = b; z = c;
		w = s;
	}

	Quaternion(const Vector3D& v, float s)
	{
		x = v.x; y = v.y; z = v.z;
		w = s;
	}

	Vector3D& GetVectorPart(void)
	{
		return (reinterpret_cast<Vector3D&>(x));
	}

	const Vector3D& GetVectorPart(void) const
	{
		return (reinterpret_cast<const Vector3D&>(x));
	}

	Matrix3D GetRotationMatrix(void);
	void SetRotationMatrix(const Matrix3D& m);
};

extern 	Quaternion operator *(const Quaternion& q1, const Quaternion& q2);
extern Vector3D Transform(const Vector3D& v, const Quaternion& q);
