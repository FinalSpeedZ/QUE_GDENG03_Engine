#pragma once

#include <string>

#include "Vec.h"

namespace Colors
{
	const vec4 RED = vec4(1.0f, 0.0f, 0.0f, 1.0f);
	const vec4 ORANGE = vec4(1.0f, 0.6f, 0.0f, 1.0f);
	const vec4 YELLOW = vec4(1.0f, 1.0f, 0.0f, 1.0f);
	const vec4 GREEN = vec4(0.0f, 1.0f, 0.0f, 1.0f);
	const vec4 BLUE = vec4(0.0f, 0.0f, 1.0f, 1.0f);
	const vec4 INDIGO = vec4(0.3f, 0.0f, 0.5f, 1.0f);
	const vec4 VIOLET = vec4(0.6f, 0.0f, 0.8f, 1.0f);
	const vec4 WHITE = vec4(1.0f, 1.0f, 1.0f, 1.0f);
	const vec4 BLACK = vec4(0.0f, 0.0f, 0.0f, 1.0f);

	inline vec4 hexToVec3(const std::string& hex)
	{
	    int red = std::stoi(hex.substr(1, 2), nullptr, 16);
	    int green = std::stoi(hex.substr(3, 2), nullptr, 16);
	    int blue = std::stoi(hex.substr(5, 2), nullptr, 16);

	    return vec4(red / 255.0f, green / 255.0f, blue / 255.0f, 1.0f);
	}
}