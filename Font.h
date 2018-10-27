#pragma once

#include <Shlwapi.h>
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>

#include <list>
#include <string>
#include <corecrt_wstring.h>

#include <iostream>
#include <WICTextureLoader.h>

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// �t�H���g��ǂݍ��ރN���X[WIP]
//
class Font {

	static ID3D11Device* device;
	static list<wstring> loadedFontDataList;

public:
	Font();
	~Font();

	static void SetInitData(ID3D11Device* device) {
		Font::device = device;
	}

	// Font�����ׂă��[�h����
	static void LoadAllFont();

	// ���[�h����Ă���Font�����ׂĊJ������
	static void UnLoadAllFont();
};

