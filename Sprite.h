#pragma once

#include "Texture.h"
#include "Rect.h"

//
// �e�N�X�`���ƕR�Â����A
// �\���͈͂��w��ł���N���X
//
class Sprite {

	Texture* texture;
	Rect rect;

public:

	Sprite(Texture* texture)
		: texture(texture) {
		//�T�C�Y�������Ă���
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