#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>
#include <iostream>

#include <vector>

#include "Shader.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// 描画するクラスの共通部分
//
class Renderer {

protected:

	static ID3D11Device* device;
	static vector<reference_wrapper<Renderer>>* rendererList;	//Renderからの参照

public:

	bool						isRender;		//描画するか
	XMMATRIX					transform;		//描画の座標データ
	ID3D11Buffer*				pVertexBuffer;	//頂点バッファーのデータ
	ID3D11VertexShader*			pVertexShader;	//頂点シェーダー
	ID3D11PixelShader*			pPixelShader;	//ピクセルシェーダー

protected:
	Renderer() {
		isRender = true;
		rendererList->push_back(*this);
	}


public:
	~Renderer() {

		//リストから削除
		auto itr = rendererList->begin();
		while (itr != rendererList->end()) {
			if (&(*itr).get() == this) {
				itr = rendererList->erase(itr);
			}
			else {
				itr++;
			}
		}

		//バッファーリソースの開放
		if (pVertexBuffer) pVertexBuffer->Release();
	}

	// サブリソースの更新時に呼ばれる
	virtual void UpdateSubResource(ID3D11DeviceContext* const context) {}

	// シェーダーのセット後に呼ばれる
	virtual void SetShaderResources(ID3D11DeviceContext* const context) {}

	// 描画されるときに呼ばれる
	virtual void Draw(ID3D11DeviceContext* const context) {}

	// シェーダーを設定する
	void SetShader(wstring name) {
		//シェーダーを取得
		Shader::GetShader(name, pVertexShader, pPixelShader);
	}


	// 生成に必要なデータを保持しておく
	static void SetRenderData(ID3D11Device* device, vector<reference_wrapper<Renderer>>& rendererList) {
		Renderer::device = device;
		Renderer::rendererList = &rendererList;
	}
};

