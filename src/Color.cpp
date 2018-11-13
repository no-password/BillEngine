#include "Color.h"

const float Color::DEFAULT_A = 0.0f;
Color::Color(float Rin, float Gin, float Bin, float Ain/* = DEFAULT_A*/) {
	R = Rin;
	G = Gin;
	B = Bin;
	A = Ain;
}
