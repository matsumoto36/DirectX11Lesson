#pragma once

#include "Renderer.h"
#include "Mesh.h"
#include "Sprite.h"

//
// スプライトをいい感じに描画するクラス
//
class SpriteRenderer : public Renderer {

	Sprite* sprite;
	Mesh* polygon;

public:
	SpriteRenderer(Sprite* sprite) {
		polygon = Primitive::GetPrimitiveMesh(PrimitiveType::Polygon);
		Init();

		SetSprite(sprite);
	}

	~SpriteRenderer() {
		delete polygon;
	}

	void Init();

	// スプライトをセットする
	void SetSprite(Sprite* sprite) {
		this->sprite = sprite;
		if (!sprite) return;
		UpdateUV();
	}

	virtual void OnUpdateSubResource(ID3D11DeviceContext* const context) override {

		context->UpdateSubresource(
			_vertexBuffer,
			0,
			nullptr,
			polygon->GetVertex().data(),
			0, 0
		);
	}

	virtual void OnDraw(ID3D11DeviceContext* const context) override {

		//context->Draw(polygon->GetVertex().size(), 0);
		context->DrawIndexed(polygon->GetIndices().size(), 0, 0);

	}

private:

	// スプライトの値に合わせてPolygonのUVを更新する
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

