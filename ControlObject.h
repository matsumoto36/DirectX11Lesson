#pragma once

#include <tchar.h>					//Microsoft�ŗL�̔ėp�e�L�X�g�̃}�b�s���O
#include <Windows.h>				//Windows�v���O�����Œʏ�K�v�ƂȂ�w�b�_�t�@�C��
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>

#include <time.h>
#include <random>

#include <math.h>
#include <vector>

#include "Time.h"
#include "Mesh.h"
#include "SpriteRenderer.h"
#include "Render.h"


#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

//
// �����������߂Ɏg�p����N���X
//
class ControlObject {

	BYTE key[256];

	Texture* walkTexture;
	Texture* texture;

	vector<Sprite*> sprites;
	Sprite* sprite;

	SpriteRenderer* renderer;

	int walkState = 0;
	float spriteChangeTime = 0.1f;
	float t = 0;

	float walkSpeed = 3;
	float scaleX = 1;
	float posX = 0;

public:
	ControlObject() {
	}
	~ControlObject() {

		if (walkTexture) delete walkTexture;
		if (texture) delete texture;

		for (size_t i = 0; i < sprites.size(); i++) {
			delete sprites[i];
		}
		if (sprite) delete sprite;

		if (renderer) delete renderer;
	}

	void Start();
	void Update();

	void Input() {

		GetKeyboardState(key);
	}

	void Quest1();
	void Quest2();


	void ResetModelTransform();
};

