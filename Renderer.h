#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>
#include <iostream>

#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// 描画するクラスの共通部分
//
class Renderer {

protected:

	static ID3D11Device* _device;
	static vector<reference_wrapper<Renderer>>* _rendererList;	//Renderからの参照

	ID3D11Buffer*					_vertexBuffer;	//頂点バッファのデータ
	ID3D11Buffer*					_indicesBuffer;	//インデックスバッファのデータ
	Material*						_material;		//マテリアルのデータ
	XMFLOAT4X4						_transform;		//描画の座標データ XMMATRIXはx86系でアラインが8になるらしい

	const Mesh*						_mesh;			//描画するメッシュのデータ

public:

	bool								IsRender;		//描画するか

protected:
	Renderer() {
		IsRender = true;
		_vertexBuffer = nullptr;
		_indicesBuffer = nullptr;
		SetTransform(XMMatrixIdentity());

		_rendererList->push_back(*this);
	}


public:
	~Renderer() {

		if(_material) delete _material;

		//リストから削除
		auto itr = _rendererList->begin();
		while (itr != _rendererList->end()) {
			if (&(*itr).get() == this) {
				itr = _rendererList->erase(itr);
			}
			else {
				itr++;
			}
		}

		//バッファーリソースの開放
		if (_vertexBuffer) _vertexBuffer->Release();
		if (_indicesBuffer) _indicesBuffer->Release();
	}

	// getter

	// 座標行列を変換して取得する
	XMMATRIX GetTransform() const {
		return XMLoadFloat4x4(&_transform);
	}

	// 座標行列を変換してセットする
	void SetTransform(const XMMATRIX transform) {
		XMStoreFloat4x4(&_transform, transform);
	}

	ID3D11Buffer* & GetVertexBuffer() {
		return _vertexBuffer;
	}

	ID3D11Buffer* & GetIndexBuffer() {
		return _indicesBuffer;
	}

	const class Material* GetMaterial() const {
		return _material;
	}

	void SetMaterial(Material* const material) {
		if (_material) delete _material;
		_material = material;
	}

	// プリミティブ タイプおよびデータの順序に関する情報をバインドする
	void SetPrimitiveTopology(ID3D11DeviceContext* const context) {
		//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST		頂点データを三角形のリストとして解釈(2つの三角形で6個の頂点)
		//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP	頂点データを三角形のストリップとして解釈(2つの三角形で4個の頂点
		context->IASetPrimitiveTopology(_mesh->GetPrimitiveTopology());
	}

	// サブリソースの更新時に呼ばれる
	virtual void OnUpdateSubResource(ID3D11DeviceContext* const context) {}

	// 描画されるときに呼ばれる
	virtual void OnDraw(ID3D11DeviceContext* const context) {}

	// 生成に必要なデータを保持しておく
	static void SetRenderData(ID3D11Device* const device, vector<reference_wrapper<Renderer>>& rendererList) {
		Renderer::_device = device;
		Renderer::_rendererList = &rendererList;
	}
};

