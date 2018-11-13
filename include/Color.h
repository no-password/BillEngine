#ifndef COLOR_H
#define COLOR_H

class Color {
	private:
		const static float DEFAULT_A;
	public:
		float R, G, B, A;
		Color(float Rin, float Gin, float Bin, float Ain = DEFAULT_A);
		Color blend(const Color, const Color);
};

#endif
