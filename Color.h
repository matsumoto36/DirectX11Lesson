#pragma once
struct Color {

	float R, G, B, A;

	Color() : R(0), G(0), B(0), A(1) {};
	Color(float r, float g, float b, float a) : R(r), G(g), B(b), A(a) {};
	~Color() {}
};

