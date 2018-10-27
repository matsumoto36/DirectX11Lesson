#pragma once

#include "Texture.h"
#include "Rect.h"

//
// テクスチャと紐づけられ、
// 表示範囲を指定できるクラス
//
class Sprite {

	Texture* texture;
	Rect rect;

public:

	Sprite(Texture* texture)
		: texture(texture) {
		//サイズを持ってくる
		auto size = texture->GetSize();
		rect.width = size.x;
		rect.height = size.y;
	}

	Sprite(Texture* texture, Rect rect)
		: texture(texture), rect(rect) {

	}

	~Sprite() {}

	Texture* const GetTexture() {
		return texture;
	}

	const Rect GetRect() {
		return rect;
	}
};