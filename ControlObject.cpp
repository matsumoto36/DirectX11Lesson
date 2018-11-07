#include "ControlObject.h"

void ControlObject::Start() {

	//�e�N�X�`���ǂݍ���
	walkTexture = new Texture(L"Resources/Texture/player.png");
	texture = new Texture(L"Resources/Texture/tex.jpg");

	//�X�v���C�g�쐬
	for (size_t i = 0; i < 7; i++) {
		sprites.push_back(new Sprite(walkTexture, Rect(64 * i, 0, 64, 64)));
	}
	sprite = new Sprite(texture);


	renderer = new SpriteRenderer(sprites[0]);
}

void ControlObject::Update() {

	static int mode = 2;

	//�L�[���͂̍X�V
	Input();

	for (auto i = 0; i < 10; i++) {
		if (key['0' + i] & 0x80) {
			if (mode != i) ResetModelTransform();
			mode = i;
		}
	}

	switch (mode) {

		case 1:	//��� 1
			Quest1();
			break;
		case 2:	//��� 2
			Quest2();
			break;
		case 3:	//��� 3
			break;
		case 4:	//��� 4
			break;
		case 5:	//��� 5
			break;
		case 6:	//��� 6
			break;
		case 7:	//��� 7
			break;
		case 8:	//��� 8
			break;
		case 9: //���EX
			break;
		case 0: //���EX2
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

	renderer->SetShader(L"Texture");
	renderer->transform = XMMatrixScaling(scaleX, 1, 1);
	renderer->transform *= XMMatrixTranslation(posX, 0, 0);

	renderer->SetSprite(sprites[walkState]);
}

void ControlObject::Quest2() {

	float speed = 1000;

	if (key[VK_LEFT] & 0x80) {
		Render::size.x -= speed * Time::GetDeltaTime();
	}
	else if (key[VK_RIGHT] & 0x80) {
		Render::size.x += speed * Time::GetDeltaTime();
	}

	if (key[VK_UP] & 0x80) {
		Render::size.y -= speed * Time::GetDeltaTime();
	}
	else if (key[VK_DOWN] & 0x80) {
		Render::size.y += speed * Time::GetDeltaTime();
	}

	renderer->SetShader(L"Blur");
	renderer->SetSprite(sprite);
	renderer->transform = XMMatrixTranslation(posX, 0, -2);

}


#pragma endregion

void ControlObject::ResetModelTransform() {


}