#include "Matrix4x4.h"

#include <iostream>

#include "Vector4D.h"

void Matrix4x4::setIdentity()
{
	::memset(mat, 0, sizeof(float) * 16);

	mat[0][0] = 1;
	mat[1][1] = 1;
	mat[2][2] = 1;
	mat[3][3] = 1;
}

void Matrix4x4::setTranslation(const Vector3D& translation)
{
	mat[3][0] = translation.x;
	mat[3][1] = translation.y;
	mat[3][2] = translation.z;
}

void Matrix4x4::setScale(const Vector3D& scale)
{
	mat[0][0] = scale.x;
	mat[1][1] = scale.y;
	mat[2][2] = scale.z;
}

void Matrix4x4::setRotationX(float x)
{
	mat[1][1] = cos(x);
	mat[1][2] = sin(x);
	mat[2][1] = -sin(x);
	mat[2][2] = cos(x);
}

void Matrix4x4::setRotationY(float y)
{
	mat[0][0] = cos(y);
	mat[0][2] = -sin(y);
	mat[2][0] = sin(y);
	mat[2][2] = cos(y);
}

void Matrix4x4::setRotationZ(float z)
{
	mat[0][0] = cos(z);
	mat[0][1] = sin(z);
	mat[1][0] = -sin(z);
	mat[1][1] = cos(z);
}

Vector3D Matrix4x4::getXDirection()
{
	return Vector3D(mat[0][0], mat[0][1], mat[0][2]);
}

Vector3D Matrix4x4::getYDirection()
{
	return Vector3D(mat[1][0], mat[1][1], mat[1][2]);
}

Vector3D Matrix4x4::getZDirection()
{
	return Vector3D(mat[2][0], mat[2][1], mat[2][2]);
}

Vector3D Matrix4x4::getTranslation()
{
	return Vector3D(mat[3][0], mat[3][1], mat[3][2]);
}

void Matrix4x4::inverse()
{
	int a, i, j;
	Matrix4x4 out;
	Vector4D v, vec[3];
	float det = 0.0f;

	det = this->getDeterminant();
	if (!det) return;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (j != i)
			{
				a = j;
				if (j > i) a = a - 1;
				vec[a].x = (this->mat[j][0]);
				vec[a].y = (this->mat[j][1]);
				vec[a].z = (this->mat[j][2]);
				vec[a].w = (this->mat[j][3]);
			}
		}
		v.cross(vec[0], vec[1], vec[2]);

		out.mat[0][i] = pow(-1.0f, i) * v.x / det;
		out.mat[1][i] = pow(-1.0f, i) * v.y / det;
		out.mat[2][i] = pow(-1.0f, i) * v.z / det;
		out.mat[3][i] = pow(-1.0f, i) * v.w / det;
	}

	this->setMatrix(out);
}

void Matrix4x4::setOrthoLH(float width, float height, float near_plane, float far_plane)
{
	setIdentity();

	mat[0][0] = 2.0f / width;
	mat[1][1] = 2.0f / height;
	mat[2][2] = 1.0f / (far_plane - near_plane);
	mat[3][2] = -(near_plane / (far_plane - near_plane));
}

void Matrix4x4::setPerspectiveFovLH(float fov, float aspect, float znear, float zfar)
{
	setIdentity();

	float yscale = 1.0f / tan(fov / 2.0f);
	float xscale = yscale / aspect;

	mat[0][0] = xscale;
	mat[1][1] = yscale;
	mat[2][2] = zfar / (zfar - znear);
	mat[2][3] = 1.0f;
	mat[3][2] = (-znear * zfar) / (zfar - znear);
}

void Matrix4x4::operator*=(const Matrix4x4& matrix)
{
	Matrix4x4 out;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			out.mat[i][j] =
				mat[i][0] * matrix.mat[0][j] + mat[i][1] * matrix.mat[1][j] +
				mat[i][2] * matrix.mat[2][j] + mat[i][3] * matrix.mat[3][j];
		}
	}

	::memcpy(mat, out.mat, sizeof(float) * 16);
}

void Matrix4x4::setMatrix(const Matrix4x4& matrix)
{
	::memcpy(mat, matrix.mat, sizeof(float) * 16);
}

float Matrix4x4::getDeterminant()
{
	Vector4D minor, v1, v2, v3;
	float det;

	v1 = Vector4D(this->mat[0][0], this->mat[1][0], this->mat[2][0], this->mat[3][0]);
	v2 = Vector4D(this->mat[0][1], this->mat[1][1], this->mat[2][1], this->mat[3][1]);
	v3 = Vector4D(this->mat[0][2], this->mat[1][2], this->mat[2][2], this->mat[3][2]);


	minor.cross(v1, v2, v3);
	det = -(this->mat[0][3] * minor.x + this->mat[1][3] * minor.y + this->mat[2][3] * minor.z +
		this->mat[3][3] * minor.w);
	return det;
}
