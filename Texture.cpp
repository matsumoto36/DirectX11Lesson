#include "Texture.h"

ID3D11Device* Texture::device = nullptr;

Texture::Texture(wstring fileName) {

	resourceView = nullptr;
	texrure = nullptr;

	auto hr = CreateWICTextureFromFile(
		device,
		fileName.c_str(),
		&texrure,
		&resourceView
	);

	if (FAILED(hr)) {
		cout << TEXT("[Error] Texture (") << fileName.c_str() << TEXT(") Failed Load.") << endl;
	}

	ID3D11Texture2D* texture2D = nullptr;
	hr = texrure->QueryInterface(&texture2D);

	if (FAILED(hr)) {
		cout << TEXT("[Error] Texture (") << fileName.c_str() << TEXT(") Failed Load.") << endl;
	}

	D3D11_TEXTURE2D_DESC desc;
	texture2D->GetDesc(&desc);
	size.x = static_cast<float>(desc.Width);
	size.y = static_cast<float>(desc.Height);
}

Texture::~Texture() {
	
	if (resourceView) resourceView->Release();

}
