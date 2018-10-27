#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Sprite.h"

//
// �X�v���C�g�����������ɕ`�悷��N���X
//
class SpriteRenderer : public Renderer {

	Sprite* sprite;
	Mesh* polygon;

public:
	SpriteRenderer(Sprite* sprite) {
		polygon = new Mesh(PrimitiveType::Polygon);
		Init();

		SetSprite(sprite);
	}

	~SpriteRenderer() {
		delete polygon;
	}

	void Init();

	// �X�v���C�g���Z�b�g����
	void SetSprite(Sprite* sprite) {
		this->sprite = sprite;
		UpdateUV();
	}

	virtual void UpdateSubResource(ID3D11DeviceContext* const context) override {

		context->UpdateSubresource(
			pVertexBuffer,
			0,
			nullptr,
			polygon->GetModelData().data(),
			0, 0
		);
	}
	virtual void SetShaderResources(ID3D11DeviceContext* const context) override {

		//�e�N�X�`����]��
		if (!sprite) return;
		if (!sprite->GetTexture()) return;

		context->PSSetShaderResources(
			0,
			1,
			&sprite->GetTexture()->resourceView);
	
	}

	virtual void Draw(ID3D11DeviceContext* const context) override {

		context->Draw(polygon->GetModelData().size(), 0);

	}

private:

	// �X�v���C�g�̒l�ɍ��킹��Polygon��UV���X�V����
	void UpdateUV() {
		auto rect = sprite->GetRect();
		auto size = sprite->GetTexture()->GetSize();

		auto startu = static_cast<float>(rect.x) / size.x;
		auto startv = static_cast<float>(rect.y) / size.y;
		auto endu = static_cast<float>(rect.x + rect.width) / size.x;
		auto endv = static_cast<float>(rect.y + rect.height) / size.y;

		polygon->SetUV(0, startu, endv);
		polygon->SetUV(1, startu, startv);
		polygon->SetUV(2, endu, endv);
		polygon->SetUV(3, endu, startv);
	}

};

