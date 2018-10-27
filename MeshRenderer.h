#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"

using namespace std;

//
// メッシュを自分で指定して描画するクラス
//
class MeshRenderer : public Renderer {

public:

	Mesh*			mesh;			//描画するメッシュのデータ
	Texture*		pTexture;		//表示するテクスチャ

	MeshRenderer(Mesh* mesh) : mesh(mesh) {

		cout << "MeshRenderer : Constructor" << endl;
		
		Init();

	}

	~MeshRenderer() {

		cout << "MeshRenderer : Destructor" << endl;
	}

	void Init();

	virtual void UpdateSubResource(ID3D11DeviceContext* const context) override {

		context->UpdateSubresource(
			pVertexBuffer,
			0,
			nullptr,
			mesh->GetModelData().data(),
				0, 0
				);
	}
	virtual void SetShaderResources(ID3D11DeviceContext* const context) override {

		//テクスチャを転送
		if (pTexture) {
			context->PSSetShaderResources(
				0,
				1,
				&pTexture->resourceView);
		}
	}

	virtual void Draw(ID3D11DeviceContext* const context) override {

		context->Draw(mesh->GetModelData().size(), 0);

	}

};

