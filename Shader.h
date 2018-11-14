#pragma once

#include <tchar.h>					//Microsoft固有の汎用テキストのマッピング
#include <Windows.h>				//Windowsプログラムで通常必要となるヘッダファイル
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>
#include <iostream>

#include <array>

#include <string>
#include <corecrt_wstring.h>
#include "FileAccess.h"
#include "ShaderVariable.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;

enum class ShaderStage;
class GeneratedShader;

//
// シェーダーを読み込んで管理するクラス
//
class Shader final {
public:

	static const size_t ShaderStageSize = 2;

private:

	static vector<vector<D3D11_INPUT_ELEMENT_DESC>> _inputLayoutDescList;

	static D3D11_INPUT_ELEMENT_DESC vertexDesc[];		//ここに定義した内容が頂点シェーダーに送られる

	static vector<GeneratedShader*> loadedShaderList;		//読み込まれているシェーダーのリスト

private:
	Shader();

public:

	static HRESULT Initialize(ID3D11Device &);
	static void Finalize();

	// 名前を指定してシェーダーを取得する
	static bool FindShader(const wstring, const ID3D11VertexShader* &, const ID3D11PixelShader* &);
	static const GeneratedShader* const FindShader(const wstring &);

	// ファイルを指定してシェーダーをコンパイルする
	static HRESULT CompileShaderFromFile(WCHAR*, LPCSTR, LPCSTR, ID3DBlob**);

private:
	// 頂点シェーダーの作成
	static HRESULT CreateVertexShader(ID3D11Device &, const wchar_t*, ID3D11VertexShader* &, ID3D11InputLayout* &, ID3D11ShaderReflection* &);
	// ピクセルシェーダーの作成
	static HRESULT CreatePixelShader(ID3D11Device &, const wchar_t*, ID3D11PixelShader* &, ID3D11ShaderReflection* &);

	//
	static DXGI_FORMAT GetDxgiFormat(D3D10_REGISTER_COMPONENT_TYPE, BYTE);

};

//
// シェーダーのステージ名
//
enum class ShaderStage {
	Vertex,
	Pixel,
};

//
// シェーダーのデータアセット
//
class GeneratedShader {

	wstring _name;

	ID3D11VertexShader* _vertexShader;
	ID3D11InputLayout* _inputLayout;

	ID3D11PixelShader* _pixelShader;

	vector<ShaderVariable*> _shaderVariables;

public:

	GeneratedShader(
		wstring name,
		ID3D11VertexShader* vertexShader,
		ID3D11InputLayout* inputLayout,
		ID3D11PixelShader* pixelShader,
		vector<ShaderVariable*> ShaderVariables
	) :
		_name(name),
		_vertexShader(vertexShader),
		_inputLayout(inputLayout),
		_pixelShader(pixelShader),
		_shaderVariables(ShaderVariables) {}

	~GeneratedShader() {
		if (_vertexShader) _vertexShader->Release();
		if (_inputLayout) _inputLayout->Release();
		if (_pixelShader) _pixelShader->Release();

		for (auto variable : _shaderVariables) {
			if (variable) delete variable;
		}
	}

	// getter
	const wstring GetName() const {
		return _name;
	}

	ID3D11VertexShader* const GetVertexShader() const {
		return _vertexShader;
	}

	ID3D11InputLayout* const GetInputLayout() const {
		return _inputLayout;
	}

	ID3D11PixelShader* const GetPixelShader() const {
		return _pixelShader;
	}

	vector<ShaderVariable*> const GetVertexShaderVariables() const {
		return _shaderVariables;
	}
};