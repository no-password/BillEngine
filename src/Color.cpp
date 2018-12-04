#include "Color.h"

#include <bits/stdc++.h>
const float Color::DEFAULT_A = 0.0f;
Color::Color(float Rin, float Gin, float Bin, float Ain/* = DEFAULT_A*/) {
	R = Rin;
	G = Gin;
	B = Bin;
	A = Ain;
}

std::string Color::getUniqueString() {
	std::ostringstream stringStream;
	stringStream << R << "," << G << "," << B << "," << A;
	return stringStream.str();
}

inline float Color::RGBValueToOpenGL(float rgb) {
	return rgb / 255.0f;
}
