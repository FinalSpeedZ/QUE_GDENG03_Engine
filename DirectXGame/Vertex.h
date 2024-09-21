#pragma once

struct vec3
{
	float x, y, z;

	vec3(float const x = 0.0f, float const y = 0.0f, float const z = 0.0f) : x(x), y(y), z(z) {}
};

struct vertex
{
	vec3 position;
	vec3 color;
};
