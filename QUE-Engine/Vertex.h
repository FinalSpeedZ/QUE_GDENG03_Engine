#pragma once

#include "Vector2D.h"
#include "Vector4D.h"
#include "Vector3D.h"

#include "Colors.h"

struct vertex
{
	Vector3D position;
	Vector4D rgba;
	Vector4D rgba1;
	Vector2D texcoord = Vector2D{0, 0};
};
