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


	MeshRenderer(const Mesh* mesh) {

		_mesh = mesh;

		cout << "MeshRenderer : Constructor" << endl;
		
		Init();

	}

	~MeshRenderer() {

		cout << "MeshRenderer : Destructor" << endl;
	}

	void Init();

	virtual void OnUpdateSubResource(ID3D11DeviceContext* const context) override {

		context->UpdateSubresource(
			_vertexBuffer,
			0,
			nullptr,
			_mesh->GetVertex().data(),
			0, 0
		);
	}

	virtual void OnDraw(ID3D11DeviceContext* const context) override {

		//context->Draw(_mesh->GetVertex().size(), 0);
		context->DrawIndexed(_mesh->GetIndices().size(), 0, 0);

	}

};

