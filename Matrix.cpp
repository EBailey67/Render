#include <math.h>
#include "Matrix.h"


Matrix3D Inverse(const Matrix3D& M)
{
	const Vector3D& a = M[0];
	const Vector3D& b = M[1];
	const Vector3D& c = M[2];

	Vector3D r0 = Cross(b, c);
	Vector3D r1 = Cross(c, a);
	Vector3D r2 = Cross(a, b);

	float invDet = 1.0F / Dot(r2, c);

	return (Matrix3D(r0.x * invDet, r0.y * invDet, r0.z * invDet,
		r1.x * invDet, r1.y * invDet, r1.z * invDet,
		r2.x * invDet, r2.y * invDet, r2.z * invDet));
}

// Listing 1.11

Matrix4D Inverse(const Matrix4D& M)
{
	const Vector3D& a = reinterpret_cast<const Vector3D&>(M[0]);
	const Vector3D& b = reinterpret_cast<const Vector3D&>(M[1]);
	const Vector3D& c = reinterpret_cast<const Vector3D&>(M[2]);
	const Vector3D& d = reinterpret_cast<const Vector3D&>(M[3]);

	const float& x = M(3, 0);
	const float& y = M(3, 1);
	const float& z = M(3, 2);
	const float& w = M(3, 3);

	Vector3D s = Cross(a, b);
	Vector3D t = Cross(c, d);
	Vector3D u = a * y - b * x;
	Vector3D v = c * w - d * z;

	float invDet = 1.0F / (Dot(s, v) + Dot(t, u));
	s *= invDet;
	t *= invDet;
	u *= invDet;
	v *= invDet;

	Vector3D r0 = Cross(b, v) + t * y;
	Vector3D r1 = Cross(v, a) - t * x;
	Vector3D r2 = Cross(d, u) + s * w;
	Vector3D r3 = Cross(u, c) - s * z;

	return (Matrix4D(r0.x, r0.y, r0.z, -Dot(b, t),
		r1.x, r1.y, r1.z, Dot(a, t),
		r2.x, r2.y, r2.z, -Dot(d, s),
		r3.x, r3.y, r3.z, Dot(c, s)));
}

Matrix3D MakeRotationX(float t)
{
	float c = static_cast<float>(cos(t));
	float s = static_cast<float>(sin(t));

	return (Matrix3D(1.0F, 0.0F, 0.0F,
		0.0F, c, -s,
		0.0F, s, c));
}

Matrix3D MakeRotationY(float t)
{
	float c = static_cast<float>(cos(t));
	float s = static_cast<float>(sin(t));

	return (Matrix3D(c, 0.0F, s,
					 0.0F, 1.0F, 0.0F,
					-s, 0.0F, c));
}

Matrix3D MakeRotationZ(float t)
{
	float c = static_cast<float>(cos(t));
	float s = static_cast<float>(sin(t));

	return (Matrix3D(c, -s, 0.0F,
		s, c, 0.0F,
		0.0F, 0.0F, 1.0F));
}


Matrix3D MakeRotation(float t, const Vector3D& a)
{
	float c = static_cast<float>(cos(t));
	float s = static_cast<float>(sin(t));
	float d = 1.0F - c;

	float x = a.x * d;
	float y = a.y * d;
	float z = a.z * d;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return (Matrix3D(c + x * a.x, axay - s * a.z, axaz + s * a.y,
		axay + s * a.z, c + y * a.y, ayaz - s * a.x,
		axaz - s * a.y, ayaz + s * a.x, c + z * a.z));
}

// Listing 2.3

Matrix3D MakeReflection(const Vector3D& a)
{
	float x = a.x * -2.0F;
	float y = a.y * -2.0F;
	float z = a.z * -2.0F;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return (Matrix3D(x * a.x + 1.0F, axay, axaz,
		axay, y * a.y + 1.0F, ayaz,
		axaz, ayaz, z * a.z + 1.0F));
}

// Listing 2.4

Matrix3D MakeInvolution(const Vector3D& a)
{
	float x = a.x * 2.0F;
	float y = a.y * 2.0F;
	float z = a.z * 2.0F;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return (Matrix3D(x * a.x - 1.0F, axay, axaz,
		axay, y * a.y - 1.0F, ayaz,
		axaz, ayaz, z * a.z - 1.0F));
}

// Listing 2.5

Matrix3D MakeScale(float sx, float sy, float sz)
{
	return (Matrix3D(sx, 0.0F, 0.0F, 0.0F, sy, 0.0F, 0.0F, 0.0F, sz));
}

// Listing 2.6

Matrix3D MakeScale(float s, const Vector3D& a)
{
	s -= 1.0F;
	float x = a.x * s;
	float y = a.y * s;
	float z = a.z * s;
	float axay = x * a.y;
	float axaz = x * a.z;
	float ayaz = y * a.z;

	return (Matrix3D(x * a.x + 1.0F, axay, axaz,
		axay, y * a.y + 1.0F, ayaz,
		axaz, ayaz, z * a.z + 1.0F));
}

Matrix3D MakeSkew(float t, const Vector3D& a, const Vector3D& b)
{
	t = static_cast<float>(tan(t));
	float x = a.x * t;
	float y = a.y * t;
	float z = a.z * t;

	return (Matrix3D(x * b.x + 1.0F, x * b.y, x * b.z,
		y * b.x, y * b.y + 1.0F, y * b.z,
		z * b.x, z * b.y, z * b.z + 1.0F));
}

Matrix3D operator *(const Matrix3D& A, const Matrix3D& B)
{
	return (Matrix3D(A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
		A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
		A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
		A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
		A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
		A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
		A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
		A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
		A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2)));
}


float Determinant(const Matrix3D& M)
{
	return (M(0, 0) * (M(1, 1) * M(2, 2) - M(1, 2) * M(2, 1))
		+ M(0, 1) * (M(1, 2) * M(2, 0) - M(1, 0) * M(2, 2))
		+ M(0, 2) * (M(1, 0) * M(2, 1) - M(1, 1) * M(2, 0)));
}



Transform4D operator *(const Transform4D& A, const Transform4D& B)
{
	return (Transform4D(
		A(0, 0) * B(0, 0) + A(0, 1) * B(1, 0) + A(0, 2) * B(2, 0),
		A(0, 0) * B(0, 1) + A(0, 1) * B(1, 1) + A(0, 2) * B(2, 1),
		A(0, 0) * B(0, 2) + A(0, 1) * B(1, 2) + A(0, 2) * B(2, 2),
		A(0, 0) * B(0, 3) + A(0, 1) * B(1, 3) + A(0, 2) * B(2, 3) + A(0, 3),
		A(1, 0) * B(0, 0) + A(1, 1) * B(1, 0) + A(1, 2) * B(2, 0),
		A(1, 0) * B(0, 1) + A(1, 1) * B(1, 1) + A(1, 2) * B(2, 1),
		A(1, 0) * B(0, 2) + A(1, 1) * B(1, 2) + A(1, 2) * B(2, 2),
		A(1, 0) * B(0, 3) + A(1, 1) * B(1, 3) + A(1, 2) * B(2, 3) + A(1, 3),
		A(2, 0) * B(0, 0) + A(2, 1) * B(1, 0) + A(2, 2) * B(2, 0),
		A(2, 0) * B(0, 1) + A(2, 1) * B(1, 1) + A(2, 2) * B(2, 1),
		A(2, 0) * B(0, 2) + A(2, 1) * B(1, 2) + A(2, 2) * B(2, 2),
		A(2, 0) * B(0, 3) + A(2, 1) * B(1, 3) + A(2, 2) * B(2, 3) + A(2, 3)));
}

Transform4D Inverse(const Transform4D& H)
{
	const Vector3D& a = H[0];
	const Vector3D& b = H[1];
	const Vector3D& c = H[2];
	const Vector3D& d = H[3];

	Vector3D s = Cross(a, b);
	Vector3D t = Cross(c, d);

	float invDet = 1.0F / Dot(s, c);

	s *= invDet;
	t *= invDet;
	Vector3D v = c * invDet;

	Vector3D r0 = Cross(b, v);
	Vector3D r1 = Cross(v, a);

	return (Transform4D(r0.x, r0.y, r0.z, -Dot(b, t),
		r1.x, r1.y, r1.z, Dot(a, t),
		s.x, s.y, s.z, -Dot(d, s)));
}


Vector3D operator *(const Transform4D& H, const Vector3D& v)
{
	return (Vector3D(H(0, 0) * v.x + H(0, 1) * v.y + H(0, 2) * v.z,
		H(1, 0) * v.x + H(1, 1) * v.y + H(1, 2) * v.z,
		H(2, 0) * v.x + H(2, 1) * v.y + H(2, 2) * v.z));
}

Point3D operator *(const Transform4D& H, const Point3D& p)
{
	return (Point3D(H(0, 0) * p.x + H(0, 1) * p.y + H(0, 2) * p.z + H(0, 3),
		H(1, 0) * p.x + H(1, 1) * p.y + H(1, 2) * p.z + H(1, 3),
		H(2, 0) * p.x + H(2, 1) * p.y + H(2, 2) * p.z + H(2, 3)));
}


Vector3D operator *(const Vector3D& n, const Transform4D& H)
{
	return (Vector3D(n.x * H(0, 0) + n.y * H(1, 0) + n.z * H(2, 0),
		n.x * H(0, 1) + n.y * H(1, 1) + n.z * H(2, 1),
		n.x * H(0, 2) + n.y * H(1, 2) + n.z * H(2, 2)));
}
