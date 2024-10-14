#pragma once

#include <iostream>
#include <memory>
#include <ostream>

#include "Vector3D.h"
#include "Vector4D.h"

class Matrix4x4
{
public:
	Matrix4x4() {};
	~Matrix4x4() {};

	void setMatrix(const Matrix4x4& matrix);

	void setIdentity();
	void setTranslation(const Vector3D& translation);
	void setScale(const Vector3D& scale);

	void setRotationX(float x);
	void setRotationY(float y);
	void setRotationZ(float z);

	Vector3D getXDirection();
	Vector3D getZDirection();
	Vector3D getTranslation();

	void setOrthoLH(float width, float height, float near_plane, float far_plane);
	void setPerspectiveFovLH(float fov, float aspect, float znear, float zfar);

	float getDeterminant();
	void inverse();

	void operator*=(const Matrix4x4& matrix);

	void print() const
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				std::cout << m_mat[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}

public:
	float m_mat[4][4];
};

