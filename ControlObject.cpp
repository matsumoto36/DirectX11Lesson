#include "ControlObject.h"

void ControlObject::Start() {

	//テクスチャ読み込み
	walkTexture = new Texture(L"Resources/Texture/player.png");

	for (size_t i = 0; i < 7; i++) {
		sprites.push_back(new Sprite(walkTexture, Rect(64 * i, 0, 64, 64)));
	}

	renderer = new SpriteRenderer(sprites[0]);
}

void ControlObject::Update() {

	static int mode = 1;

	//キー入力の更新
	Input();

	for (auto i = 0; i < 10; i++) {
		if (key['0' + i] & 0x80) {
			if (mode != i) ResetModelTransform();
			mode = i;
		}
	}

	switch (mode) {

		case 1:	//問題 1
			Quest1();
			break;
		case 2:	//問題 2
			break;
		case 3:	//問題 3
			break;
		case 4:	//問題 4
			break;
		case 5:	//問題 5
			break;
		case 6:	//問題 6
			break;
		case 7:	//問題 7
			break;
		case 8:	//問題 8
			break;
		case 9: //問題EX
			break;
		case 0: //問題EX2
			break;

		default:
			break;
	}
}

#pragma region QuestMethod

void ControlObject::Quest1() {

	t += Time::GetDeltaTime();
	if (t >= spriteChangeTime * 6) {
		t -= spriteChangeTime * 6;
	}
	
	int walkState = static_cast<int>(floorf(t / spriteChangeTime)) + 1;


	if (key[VK_LEFT] & 0x80) {
		scaleX = -1;
		posX -= walkSpeed * Time::GetDeltaTime();
	}
	else if(key[VK_RIGHT] & 0x80){
		scaleX = 1;
		posX += walkSpeed * Time::GetDeltaTime();
	}
	else {
		walkState = 0;
	}

	renderer->transform = XMMatrixScaling(scaleX, 1, 1);
	renderer->transform *= XMMatrixTranslation(posX, 0, 0);

	renderer->SetSprite(sprites[walkState]);
}

#pragma endregion

void ControlObject::ResetModelTransform() {


}