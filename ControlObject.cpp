#include "ControlObject.h"

void ControlObject::Start() {

	//モデルをロード
	_fbxLoader = new FBXLoader();

	//レンダラーの設定
	//TODO FBXのモデルが出ない
	auto model = _fbxLoader->GetMesh(string("Test"));
	//auto model = Primitive::CreatePrimitiveMesh(PrimitiveType::Polygon);
	meshRenderer = new MeshRenderer(model);

	auto material = meshRenderer->GetMaterial();
	//色の設定
	Color c = { 1, 1, 1, 1 };
	material->SetColor("Color", c);

	//ライト設定
	material->SetFloat3("Light", Vector3(0, 0, 5));

	//カメラ移動
	Render::GetCamera().SetPosition(Vector3(0, 0, -5));

	////テクスチャ読み込み
	//textures.push_back(new Texture(L"Resources/Texture/player.png"));
	//textures.push_back(new Texture(L"Resources/Texture/maho.jpg"));
	//textures.push_back(new Texture(L"Resources/Texture/mask.jpg"));
	//textures.push_back(new Texture(L"Resources/Texture/renga.jpg"));
	//textures.push_back(new Texture(L"Resources/Texture/renga_n.png"));

	////スプライト作成
	//for (size_t i = 0; i < 7; i++) {
	//	sprites.push_back(new Sprite(textures[0], Rect(64 * i, 0, 64, 64)));
	//}
	//sprite = new Sprite(textures[2]);

	//spriteRenderer = new SpriteRenderer();

	////データ転送
	//auto mat = new Material(L"Texture");
	//mat->SetFloat3("Light", Vector3(0, 0, 1));
	//mat->SetTexture("MainTexture", *textures[3]);
	//mat->SetTexture("NormalTexture", *textures[4]);

	//spriteRenderer->SetMaterial(mat);
}

void ControlObject::Update() {

	static int mode = 5;

	//キー入力の更新
	Input();

	for (auto i = 0; i < 10; i++) {
		if (key['0' + i] & 0x80) {
			if (mode != i) ResetModelTransform();
			mode = i;
		}
	}

	switch (mode) {

		case 1:	//問題 1
			//Quest1();
			break;
		case 2:	//問題 2
			//Quest2();
			break;
		case 3:	//問題 3
			//Quest3();
			break;
		case 4:	//問題 4
			//Quest4();
			break;
		case 5:	//問題 5
			Quest5();
			break;
		case 6:	//問題 6
			break;
		case 7:	//問題 7
			break;
		case 8:	//問題 8
			break;
		case 9: //問題EX
			break;
		case 0: //問題EX2
			break;

		default:
			break;
	}
}

#pragma region QuestMethod

void ControlObject::Quest1() {

	t += Time::GetDeltaTime();
	if (t >= spriteChangeTime * 6) {
		t -= spriteChangeTime * 6;
	}
	
	int walkState = static_cast<int>(floorf(t / spriteChangeTime)) + 1;


	if (key[VK_LEFT] & 0x80) {
		scaleX = -1;
		posX -= walkSpeed * Time::GetDeltaTime();
	}
	else if(key[VK_RIGHT] & 0x80){
		scaleX = 1;
		posX += walkSpeed * Time::GetDeltaTime();
	}
	else {
		walkState = 0;
	}

	//renderer->SetShader(L"Texture");
	auto transform = spriteRenderer->GetTransform();
	transform = XMMatrixScaling(scaleX, 1, 1);
	transform *= XMMatrixTranslation(posX, 0, 0);
	spriteRenderer->SetTransform(transform);

	spriteRenderer->SetSprite(sprites[walkState]);
}

void ControlObject::Quest2() {

	float speed = 1000;

	if (key[VK_LEFT] & 0x80) {
		//Render::size.x -= speed * Time::GetDeltaTime();
	}
	else if (key[VK_RIGHT] & 0x80) {
		//Render::size.x += speed * Time::GetDeltaTime();
	}

	if (key[VK_UP] & 0x80) {
		//Render::size.y -= speed * Time::GetDeltaTime();
	}
	else if (key[VK_DOWN] & 0x80) {
		//Render::size.y += speed * Time::GetDeltaTime();
	}

	//renderer->SetShader(L"Blur");
	//renderer->SetSprite(sprite);
	//auto transform = renderer->GetTransform();
	//transform = XMMatrixTranslation(posX, 0, -2);
	//renderer->SetTransform(transform);
}

void ControlObject::Quest3() {

	float speed = 1;

	if (key[VK_RIGHT] & 0x80) {
		ratio -= Time::GetDeltaTime() * speed;
		if (ratio < 0) ratio = 0;
	}
	else if (key[VK_LEFT] & 0x80) {
		ratio += Time::GetDeltaTime() * speed;
		if (ratio > .99) ratio = .99;
	}

	if (auto mat = spriteRenderer->GetMaterial()) {
		mat->SetFloat("Ratio", ratio);
	}
}


void ControlObject::Quest4() {

	static auto rotTex = 0.0f;
	//static auto rotLight = 0.0f;
	static auto lightPos = Vector3(0, 0, 1);

	const auto texSpeed = 2.0f;
	const auto lightSpeed = 2.0f;

	auto angle = 0;

	if (key[VK_LEFT] & 0x80) {
		angle = 1;
	}

	else if (key[VK_RIGHT] & 0x80) {
		angle = -1;
	}

	rotTex += angle * texSpeed * Time::GetDeltaTime();

	auto transform = spriteRenderer->GetTransform();
	transform = XMMatrixIdentity();
	transform *= XMMatrixRotationY(rotTex);
	transform *= XMMatrixTranslation(0, 0, -2);
	spriteRenderer->SetTransform(transform);

	auto spd = lightSpeed * Time::GetDeltaTime();

	if (key['A'] & 0x80) {
		lightPos.x += spd;
	}
	else if (key['D'] & 0x80) {
		lightPos.x -= spd;
	}
	else if (key['W'] & 0x80) {
		lightPos.y -= spd;
	}
	else if (key['S'] & 0x80) {
		lightPos.y += spd;
	}

	//rotLight += angle * lightSpeed * Time::GetDeltaTime();
	//Vector3(sin(rotLight), 0, cos(rotLight))
	spriteRenderer
		->GetMaterial()
		->SetFloat3("Light", lightPos);

}

void ControlObject::Quest5() {

	//カメラ移動
	auto cameraPos = Render::GetCamera().GetPosition();
	const auto speed = 3.0f;

	if (key['A'] & 0x80) {
		cameraPos.x += speed * Time::GetDeltaTime();
	}
	if (key['D'] & 0x80) {
		cameraPos.x -= speed * Time::GetDeltaTime();
	}
	if (key[VK_SPACE] & 0x80) {
		cameraPos.y += speed * Time::GetDeltaTime();
	}
	if (key[VK_SHIFT] & 0x80) {
		cameraPos.y -= speed * Time::GetDeltaTime();
	}
	if (key['W'] & 0x80) {
		cameraPos.z -= speed * Time::GetDeltaTime();
	}
	if (key['S'] & 0x80) {
		cameraPos.z += speed * Time::GetDeltaTime();
	}

	Render::GetCamera().SetPosition(cameraPos);

	//モデル回転
	static float rotY = 0;

	if (key[VK_LEFT] & 0x80) {
		rotY -= speed * Time::GetDeltaTime();
	}
	if (key[VK_RIGHT] & 0x80) {
		rotY += speed * Time::GetDeltaTime();
	}
	auto transform = meshRenderer->GetTransform();
	transform = XMMatrixIdentity();
	transform *= XMMatrixRotationY(rotY);
	meshRenderer->SetTransform(transform);

	//ライト移動
	auto material = meshRenderer->GetMaterial();
	auto lightPos = material->GetFloat3("Light");
	if (key['J'] & 0x80) {
		lightPos.x -= speed * Time::GetDeltaTime();
	}
	if (key['L'] & 0x80) {
		lightPos.x += speed * Time::GetDeltaTime();
	}
	if (key['U'] & 0x80) {
		lightPos.y -= speed * Time::GetDeltaTime();
	}
	if (key['O'] & 0x80) {
		lightPos.y += speed * Time::GetDeltaTime();
	}
	if (key['I'] & 0x80) {
		lightPos.z += speed * Time::GetDeltaTime();
	}
	if (key['K'] & 0x80) {
		lightPos.z -= speed * Time::GetDeltaTime();
	}
	material->SetFloat3("Light", lightPos);
}

#pragma endregion

void ControlObject::ResetModelTransform() {


}