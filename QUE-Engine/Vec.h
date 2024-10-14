#pragma once

#include "Vector3D.h"

struct vec4
{
	float x, y, z, w;

	vec4(float const x = 0.0f, float const y = 0.0f, float const z = 0.0f, float const w = 0.0f) : x(x), y(y), z(z), w(w) {}

	vec4(const Vector3D& vec) : x(vec.x), y(vec.y), z(vec.z), w(1) {}
};