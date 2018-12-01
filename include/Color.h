#ifndef COLOR_H
#define COLOR_H

class Color {
	private:
		const static float DEFAULT_A;
	public:
		float R, G, B, A;
		Color(float Rin = 0.0f, float Gin = 0.0f, float Bin = 0.0f, float Ain = DEFAULT_A);
		Color blend(const Color, const Color);
};

#endif
