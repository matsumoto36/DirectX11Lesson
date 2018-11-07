#pragma once

#include <tchar.h>					//Microsoft固有の汎用テキストのマッピング
#include <Windows.h>				//Windowsプログラムで通常必要となるヘッダファイル
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>
#include <iostream>

#include <unordered_map>			//シェーダーを管理するために利用
#include <string>
#include <corecrt_wstring.h>
#include "FileAccess.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;

//
// シェーダーを読み込んで管理するクラス
//
class Shader final {

	static ID3D11InputLayout*	pVertexLayout;			//入力アセンブラーステージの入力データにアクセス
	static D3D11_INPUT_ELEMENT_DESC vertexDesc[];		//ここに定義した内容が頂点シェーダーに送られる
	static vector<wstring> shaderNameList;				//読み込まれているシェーダーのリスト

private:
	Shader();

public:

	static unordered_map<wstring, ID3D11VertexShader*>	pVertexShaderMap;	//頂点シェーダーステージを制御する実行可能プログラム (頂点シェーダー) を管理
	static unordered_map<wstring, ID3D11PixelShader*>	pPixelShaderMap;	//ピクセルシェーダーステージを制御する実行可能プログラム (ピクセル シェーダー) を管理

	static HRESULT Initialize(ID3D11Device* device);
	static void Finalize();

	// 名前を指定してシェーダーを取得する
	static void GetShader(wstring name, ID3D11VertexShader* &pVertexShader, ID3D11PixelShader* &pPixelShader);

	// その名前のシェーダーが存在しているか調べる
	static bool IsValidShader(wstring name);

	// 頂点シェーダーの作成
	static HRESULT CreateVertexShader(ID3D11Device* device, const wchar_t* vs, ID3D11VertexShader* &pVertexShader);
	// ピクセルシェーダーの作成
	static HRESULT CreatePixelShader(ID3D11Device* device, const wchar_t* ps, ID3D11PixelShader* &pPixelShader);

	// ファイルを指定してシェーダーをコンパイルする
	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// 入力アセンブラーステージに入力レイアウトオブジェクトをバインドする
	static void BindInputLayout(ID3D11DeviceContext* pDeviceContext);
};

