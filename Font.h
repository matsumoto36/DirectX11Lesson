#pragma once

#include <Shlwapi.h>
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>

#include <list>
#include <string>
#include <corecrt_wstring.h>

#include <iostream>
#include <WICTextureLoader.h>

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// フォントを読み込むクラス[WIP]
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

	// Fontをすべてロードする
	static void LoadAllFont();

	// ロードされているFontをすべて開放する
	static void UnLoadAllFont();
};

