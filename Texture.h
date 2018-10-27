#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>

#include <iostream>
#include <string>
#include <WICTextureLoader.h>

#include "Vector2.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// �摜��ǂݍ��ރN���X
//
class Texture {

	static ID3D11Device* device;

	Vector2 size;

public:
	
	ID3D11ShaderResourceView* resourceView;
	ID3D11Resource* texrure;

	// �t�@�C�����炻�̂܂ܐ���
	Texture(wstring fileName);

	~Texture();

	static void SetInitData(ID3D11Device* device) {
		Texture::device = device;
	}

	Vector2 GetSize() {
		return size;
	}

};

