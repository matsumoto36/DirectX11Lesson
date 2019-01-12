#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Sprite.h"

//
// �X�v���C�g�����������ɕ`�悷��N���X
//
class SpriteRenderer : public Renderer {

	Sprite* sprite;

public:
	SpriteRenderer(Sprite* sprite = nullptr) {
		_mesh = Primitive::CreatePrimitiveMesh(PrimitiveType::Polygon);
		Init();

		SetSprite(sprite);
	}

	~SpriteRenderer() {
		delete _mesh;
	}

	void Init();

	// �X�v���C�g���Z�b�g����
	void SetSprite(Sprite* sprite) {
		this->sprite = sprite;
		if (!sprite) return;
			 
		_material->SetTexture("MainTexture", *sprite->GetTexture());
		UpdateUV();
	}

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

		//context->Draw(polygon->GetVertex().size(), 0);
		context->DrawIndexed(_mesh->GetIndices().size(), 0, 0);

	}

private:

	// �X�v���C�g�̒l�ɍ��킹��Polygon��UV���X�V����
	void UpdateUV() {
		auto rect = sprite->GetRect();
		auto size = sprite->GetTexture()->GetSize();

		auto startu = static_cast<float>(rect.x) / size.x;
		auto startv = static_cast<float>(rect.y) / size.y;
		//auto endu = static_cast<float>(rect.x + rect.width) / size.x;
		//auto endv = static_cast<float>(rect.y + rect.height) / size.y;

		//UV����̓V�F�[�_�[�ł�邱��
		//polygon->SetUV(0, startu, endv);
		//polygon->SetUV(1, startu, startv);
		//polygon->SetUV(2, endu, endv);
		//polygon->SetUV(3, endu, startv);

		_material->SetFloat2("Offset", Vector2(startu, startv));
		_material->SetFloat2("Count", Vector2(rect.width / size.x, rect.height / size.y));
	}

};

