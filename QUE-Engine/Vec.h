#pragma once

#include "Vector3D.h"

struct vec3
{
	float x, y, z;

	vec3() : x(0), y(0), z(0) {}
	vec3(float const x) : x(x), y(x), z(x) {}
	vec3(float const x, float const y, float const z) : x(x), y(y), z(z) {}

	vec3 operator+(const vec3& other) const
	{
		return vec3(x + other.x, y + other.y, z + other.z);
	}

	vec3 operator-(const vec3& other) const
	{
		return vec3(x - other.x, y - other.y, z - other.z);
	}
};

struct vec4
{
	float x, y, z, w;

	vec4(const vec3& vec, float w = 1.0f) : x(vec.x), y(vec.y), z(vec.z), w(w) {}

	vec4(float const x = 0.0f, float const y = 0.0f, float const z = 0.0f, float const w = 0.0f) : x(x), y(y), z(z), w(w) {}

	vec4(const Vector3D& vec) : x(vec.m_x), y(vec.m_y), z(vec.m_z), w(1) {}
};