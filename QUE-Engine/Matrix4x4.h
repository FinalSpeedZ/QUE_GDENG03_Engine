#pragma once

#include <iostream>
#include <memory>

#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4();
	~Matrix4x4() {};

	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);

	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);

	Vector3D getXDirection();
	Vector3D getYDirection();
	Vector3D getZDirection();
	void setZDirection(Vector3D zDir);

	void inverse();

	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);

	void operator*=(const Matrix4x4& matrix);
	Matrix4x4 operator*(const Matrix4x4& matrix) const;
	Vector4D operator*(const Vector4D& vec) const;

	void setMatrix(const Matrix4x4& matrix);
	void setMatrix(float matrix[4][4]);
	float* getMatrix();

private:
	float getDeterminant();

public:
	float mat[4][4];
};

