#pragma once
#include "Vector.h"


class Matrix3D
{
private:
	float		n[3][3];

public:
	Matrix3D() = default;

	Matrix3D(float n00, float n01, float n02,
			 float n10, float n11, float n12,
			 float n20, float n21, float n22)
	{
		n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
		n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
		n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
	}

	Matrix3D(const Vector3D& a, const Vector3D& b, const Vector3D& c)
	{
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
	}

	float& operator ()(int i, int j)
	{
		return (n[j][i]);
	}

	const float& operator ()(int i, int j) const
	{
		return (n[j][i]);
	}

	Vector3D& operator [](int j)
	{
		return (*reinterpret_cast<Vector3D*>(n[j]));
	}

	const Vector3D& operator [](int j) const
	{
		return (*reinterpret_cast<const Vector3D*>(n[j]));
	}
};


class Transform4D;

extern Matrix3D MakeRotationX(float t);
extern Matrix3D MakeRotationY(float t);
extern Matrix3D MakeRotationZ(float t);
extern Matrix3D MakeRotation(float t, const Vector3D& a);
extern Matrix3D MakeReflection(const Vector3D& a);
extern Matrix3D MakeInvolution(const Vector3D& a);
extern Matrix3D MakeScale(float sx, float sy, float sz);
extern Matrix3D MakeScale(float s, const Vector3D& a);
extern Matrix3D MakeSkew(float t, const Vector3D& a, const Vector3D& b);
extern Matrix3D operator *(const Matrix3D& A, const Matrix3D& B);
extern Vector3D operator *(const Matrix3D& M, const Vector3D& v);
extern Vector3D operator *(const Transform4D& H, const Vector3D& v);


// 4D version

class Matrix4D
{
protected:
	float		n[4][4];

public:
	Matrix4D() = default;

	Matrix4D(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23,
		float n30, float n31, float n32, float n33)
	{
		n[0][0] = n00; n[0][1] = n10; n[0][2] = n20; n[0][3] = n30;
		n[1][0] = n01; n[1][1] = n11; n[1][2] = n21; n[1][3] = n31;
		n[2][0] = n02; n[2][1] = n12; n[2][2] = n22; n[2][3] = n32;
		n[3][0] = n03; n[3][1] = n13; n[3][2] = n23; n[3][3] = n33;
	}

	Matrix4D(const Vector4D& a, const Vector4D& b, const Vector4D& c, const Vector4D& d)
	{
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z; n[0][3] = a.w;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z; n[1][3] = b.w;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z; n[2][3] = c.w;
		n[3][0] = d.x; n[3][1] = d.y; n[3][2] = d.z; n[3][3] = d.w;
	}

	float& operator ()(int i, int j)
	{
		return (n[j][i]);
	}

	const float& operator ()(int i, int j) const
	{
		return (n[j][i]);
	}

	Vector4D& operator [](int j)
	{
		return (*reinterpret_cast<Vector4D*>(n[j]));
	}

	const Vector4D& operator [](int j) const
	{
		return (*reinterpret_cast<const Vector4D*>(n[j]));
	}
};

extern float Determinant(const Matrix3D& M);
extern Matrix3D Inverse(const Matrix3D& M);
extern Matrix4D Inverse(const Matrix4D& M);

class Transform4D : public Matrix4D
{
public:
	Transform4D() = default;

	Transform4D(float n00, float n01, float n02, float n03,
		float n10, float n11, float n12, float n13,
		float n20, float n21, float n22, float n23)
	{
		n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
		n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
		n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
		n[3][0] = n03; n[3][1] = n13; n[3][2] = n23;

		n[0][3] = n[1][3] = n[2][3] = 0.0F;
		n[3][3] = 1.0F;
	}

	Transform4D(const Vector3D& a, const Vector3D& b,
		const Vector3D& c, const Point3D& p)
	{
		n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
		n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
		n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
		n[3][0] = p.x; n[3][1] = p.y; n[3][2] = p.z;

		n[0][3] = n[1][3] = n[2][3] = 0.0F;
		n[3][3] = 1.0F;
	}

	Vector3D& operator [](int j)
	{
		return (*reinterpret_cast<Vector3D*>(n[j]));
	}

	const Vector3D& operator [](int j) const
	{
		return (*reinterpret_cast<const Vector3D*>(n[j]));
	}

	const Point3D& GetTranslation(void) const
	{
		return (*reinterpret_cast<const Point3D*>(n[3]));
	}

	void SetTranslation(const Point3D& p)
	{
		n[3][0] = p.x;
		n[3][1] = p.y;
		n[3][2] = p.z;
	}
};

extern Transform4D Inverse(const Transform4D& H);

