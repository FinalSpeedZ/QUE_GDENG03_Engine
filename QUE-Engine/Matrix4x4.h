#pragma once

#include <memory>

#include "Vector3D.h"

class Matrix4x4
{
public:
	Matrix4x4() {};
	~Matrix4x4() {};

	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);

	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);

	void inverse();

	void setOrthoLH(float width, float height, float near_plane, float far_plane);

	void operator*=(const Matrix4x4& matrix);

	void setMatrix(const Matrix4x4& matrix);

private:
	float getDeterminant();

private:
	float mat[4][4];
};

