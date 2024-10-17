#pragma once

#include <string>

#include "Vector4D.h"

namespace Colors
{
	const Vector4D RED = Vector4D(1.0f, 0.0f, 0.0f, 1.0f);
	const Vector4D ORANGE = Vector4D(1.0f, 0.6f, 0.0f, 1.0f);
	const Vector4D YELLOW = Vector4D(1.0f, 1.0f, 0.0f, 1.0f);
	const Vector4D GREEN = Vector4D(0.0f, 1.0f, 0.0f, 1.0f);
	const Vector4D BLUE = Vector4D(0.0f, 0.0f, 1.0f, 1.0f);
	const Vector4D INDIGO = Vector4D(0.3f, 0.0f, 0.5f, 1.0f);
	const Vector4D VIOLET = Vector4D(0.6f, 0.0f, 0.8f, 1.0f);
	const Vector4D WHITE = Vector4D(1.0f, 1.0f, 1.0f, 1.0f);
	const Vector4D BLACK = Vector4D(0.0f, 0.0f, 0.0f, 1.0f);

	inline Vector4D hexToVec3(const std::string& hex)
	{
	    int red = std::stoi(hex.substr(1, 2), nullptr, 16);
	    int green = std::stoi(hex.substr(3, 2), nullptr, 16);
	    int blue = std::stoi(hex.substr(5, 2), nullptr, 16);

	    return Vector4D(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
	}
}