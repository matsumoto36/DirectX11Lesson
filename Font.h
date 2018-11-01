#pragma once

#include <Shlwapi.h>
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>

#include <unordered_map>			//�t�H���g���Ǘ����邽�߂ɗ��p
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
class Font final {

	static ID3D11DeviceContext* deviceContext;
	static unordered_map<string, DESIGNVECTOR> loadedFontDataList;

public:

	static void SetInitData(ID3D11DeviceContext* deviceContext) {
		Font::deviceContext = deviceContext;
	}

	// Font�����ׂă��[�h����
	static void LoadAllFont();

	// ���[�h����Ă���Font�����ׂĊJ������
	static void UnLoadAllFont();

private:


};

