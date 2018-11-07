#pragma once

#include <tchar.h>					//Microsoft固有の汎用テキストのマッピング
#include <Windows.h>				//Windowsプログラムで通常必要となるヘッダファイル
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>

#include <time.h>
#include <random>

#include <math.h>
#include <vector>

#include "Time.h"
#include "Mesh.h"
#include "SpriteRenderer.h"
#include "Render.h"


#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

//
// 問題を解くために使用するクラス
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

