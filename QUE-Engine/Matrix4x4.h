#pragma once

#include <iostream>
#include <memory>

#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4() {};
	~Matrix4x4() {};

	void setIdentity();
	void setTranslation(const Vector3D& translation);
	Vector3D getTranslation();
	void setScale(const Vector3D& scale);

	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);

	Vector3D getXDirection();
	Vector3D getYDirection();
	Vector3D getZDirection();
	void setZDirection(Vector3D zDir);

	Matrix4x4 inverse();

	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);

	void operator*=(const Matrix4x4& matrix);
	Matrix4x4 operator*(const Matrix4x4& matrix) const;
	Vector4D operator*(const Vector4D& vec) const;

	void setMatrix(const Matrix4x4& matrix);

	void print() const
	{
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				std::cout << mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}



private:
	float getDeterminant();

public:
	float mat[4][4];
};

