#pragma once

struct vec3
{
	float x, y, z;

	vec3(float const x = 0.0f, float const y = 0.0f, float const z = 0.0f) : x(x), y(y), z(z) {}
};

struct vec4
{
	float x, y, z, w;

	vec4(float const x = 0.0f, float const y = 0.0f, float const z = 0.0f, float const w = 0.0f) : x(x), y(y), z(z), w(w) {}
};

struct vertex
{
	vec3 position;
	vec4 rgba;
};
