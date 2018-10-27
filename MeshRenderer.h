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
	Texture*		pTexture;		//�\������e�N�X�`��

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

		//�e�N�X�`����]��
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

