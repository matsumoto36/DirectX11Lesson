#pragma once

struct Rect {

	int x, y, width, height;

	Rect(int x = 0, int y = 0, int width = 0, int height = 0)
		: x(x), y(y), width(width), height(height) {

	}

	~Rect(){}
};

