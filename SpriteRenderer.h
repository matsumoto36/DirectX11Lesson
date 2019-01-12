#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Sprite.h"

//
// スプライトをいい感じに描画するクラス
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

	// スプライトをセットする
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

	// スプライトの値に合わせてPolygonのUVを更新する
	void UpdateUV() {
		auto rect = sprite->GetRect();
		auto size = sprite->GetTexture()->GetSize();

		auto startu = static_cast<float>(rect.x) / size.x;
		auto startv = static_cast<float>(rect.y) / size.y;
		//auto endu = static_cast<float>(rect.x + rect.width) / size.x;
		//auto endv = static_cast<float>(rect.y + rect.height) / size.y;

		//UV操作はシェーダーでやること
		//polygon->SetUV(0, startu, endv);
		//polygon->SetUV(1, startu, startv);
		//polygon->SetUV(2, endu, endv);
		//polygon->SetUV(3, endu, startv);

		_material->SetFloat2("Offset", Vector2(startu, startv));
		_material->SetFloat2("Count", Vector2(rect.width / size.x, rect.height / size.y));
	}

};

