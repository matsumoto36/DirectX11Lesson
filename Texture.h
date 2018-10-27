#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>

#include <iostream>
#include <string>
#include <WICTextureLoader.h>

#include "Vector2.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// 画像を読み込むクラス
//
class Texture {

	static ID3D11Device* device;

	Vector2 size;

public:
	
	ID3D11ShaderResourceView* resourceView;
	ID3D11Resource* texrure;

	// ファイルからそのまま生成
	Texture(wstring fileName);

	~Texture();

	static void SetInitData(ID3D11Device* device) {
		Texture::device = device;
	}

	Vector2 GetSize() {
		return size;
	}

};

