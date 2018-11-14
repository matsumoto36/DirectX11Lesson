#pragma once

#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"

using namespace std;

//
// ���b�V���������Ŏw�肵�ĕ`�悷��N���X
//
class MeshRenderer : public Renderer {

public:

	Mesh*			mesh;			//�`�悷�郁�b�V���̃f�[�^

	MeshRenderer(Mesh* mesh) : mesh(mesh) {

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
			mesh->GetVertex().data(),
				0, 0
				);
	}

	virtual void OnDraw(ID3D11DeviceContext* const context) override {

		context->Draw(mesh->GetVertex().size(), 0);

	}

};

