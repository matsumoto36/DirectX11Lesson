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

#include "FBXLoader.h"
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

	FBXLoader* _fbxLoader;

	BYTE key[256];

	vector<Texture*> textures;

	vector<Sprite*> sprites;
	Sprite* sprite;

	SpriteRenderer* spriteRenderer;
	MeshRenderer* meshRenderer;

	int walkState = 0;
	float spriteChangeTime = 0.1f;
	float t = 0;

	float walkSpeed = 3;
	float scaleX = 1;
	float posX = 0;

	float ratio = 0;

public:
	ControlObject() {
	}
	~ControlObject() {

		if (_fbxLoader) delete _fbxLoader;

		for (auto tex : textures) {
			if (tex) delete tex;
		}
		textures.clear();

		for (size_t i = 0; i < sprites.size(); i++) {
			delete sprites[i];
		}
		if (sprite) delete sprite;

		if (spriteRenderer) delete spriteRenderer;
	}

	void Start();
	void Update();

	void Input() {

		GetKeyboardState(key);
	}

	void Quest1();
	void Quest2();
	void Quest3();
	void Quest4();
	void Quest5();


	void ResetModelTransform();
};

