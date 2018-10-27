#include "Shader.h"

#pragma region DefineStaticMember

ID3D11InputLayout*							Shader::pVertexLayout = nullptr;
unordered_map<wstring, ID3D11VertexShader*>	Shader::pVertexShaderMap;
unordered_map<wstring, ID3D11PixelShader*>	Shader::pPixelShaderMap;

D3D11_INPUT_ELEMENT_DESC Shader::vertexDesc[]{
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,								D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
};

#pragma endregion


HRESULT Shader::Initialize(ID3D11Device* device) {

	//ロードするシェーダーの一覧
	wstring loadingShaderNames[] = {
		L"Unlit",
		L"Texture",
	};

	//シェーダーを作成
	for (auto item : loadingShaderNames) {

		pVertexShaderMap.emplace(item, nullptr);
		pPixelShaderMap.emplace(item, nullptr);

		auto basePath = L"Shader/";
		auto vertexShaderFileName = basePath + item + L"/VertexShader.hlsl";
		auto pixelShaderFileName = basePath + item + L"/PixelShader.hlsl";

		if (FAILED(CreateVertexShader(device, (vertexShaderFileName).c_str(), pVertexShaderMap[item]))) return E_FAIL;
		if (FAILED(CreatePixelShader(device, (pixelShaderFileName).c_str(), pPixelShaderMap[item]))) return E_FAIL;
	}

	return S_OK;
}

void Shader::Finalize() {

	//シェーダーを開放
	pVertexShaderMap.clear();
	pPixelShaderMap.clear();

	//入力レイアウトの開放
	if (pVertexLayout) pVertexLayout->Release();
}

//
// 名前を指定してシェーダーを取得する
//
void Shader::GetShader(wstring name, ID3D11VertexShader* &pVertexShader, ID3D11PixelShader* &pPixelShader) {
	pVertexShader = pVertexShaderMap[name];
	pPixelShader = pPixelShaderMap[name];
}

//
// 頂点シェーダーの作成
//
HRESULT Shader::CreateVertexShader(ID3D11Device* device, const wchar_t* vs, ID3D11VertexShader* &pVertexShader) {
	
	ID3DBlob* pVSBlob = nullptr;
	auto hr = S_OK;

	//頂点シェーダーをコンパイル
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)vs,
		"main",
		"vs_4_0",
		&pVSBlob
	);

	//頂点シェーダーを作成
	hr = device->CreateVertexShader(
		pVSBlob->GetBufferPointer(),	//コンパイル済みシェーダーへのポインタ
		pVSBlob->GetBufferSize(),		//コンパイル済み頂点シェーダーのサイズ
		nullptr,						//クラスリンクインターフェイスへのポインタ
		&pVertexShader				//ID3D11VertexShader インターフェイスへのポインタ
	);

	if (FAILED(hr)) return E_FAIL;

	//入力レイアウトを作成
	hr = device->CreateInputLayout(
		vertexDesc,					//入力アセンブラーステージの入力データ型の配列
		ARRAYSIZE(vertexDesc),		//入力要素の配列内の入力データ型の数
		pVSBlob->GetBufferPointer(),	//コンパイル済みシェーダーへのポインタ
		pVSBlob->GetBufferSize(),		//コンパイル済み頂点シェーダーのサイズ
		&pVertexLayout				//作成される入力レイアウト オブジェクトへのポインタ
	);
	pVSBlob->Release();

	return hr;
}

//
// ピクセルシェーダーの作成
//
HRESULT Shader::CreatePixelShader(ID3D11Device* device, const wchar_t* ps, ID3D11PixelShader* &pPixelShader) {

	ID3DBlob* pPSBlob = nullptr;
	auto hr = S_OK;

	//ピクセルシェーダーをコンパイル
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)ps,
		"main",
		"ps_4_0",
		&pPSBlob
	);

	//ピクセルシェーダーの作成
	hr = device->CreatePixelShader(
		pPSBlob->GetBufferPointer(),		//コンパイル済みシェーダーへのポインタ
		pPSBlob->GetBufferSize(),			//コンパイル済みピクセルシェーダーのサイズ
		nullptr,							//クラスリンクインターフェイスへのポインタ
		&pPixelShader						//ID3D11PixelShader インターフェイスへのポインタ
	);
	pPSBlob->Release();

	return hr;
}

//
// ファイルを指定してシェーダーをコンパイルする
//
HRESULT Shader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {

	HRESULT hr = S_OK;

	//コンパイラがHLSLコードをコンパイルする方法を指定
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;	//厳密なコンパイルを強制

	#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;					//デバッグ情報をコードに挿入する
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;		//最適化ステップをスキップする

	#endif // DEBUG

														//コンパイル後のバイナリデータを格納する変数
	ID3DBlob* pErrorBlob = nullptr;

	//ファイルからシェーダーをコンパイル
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr)) {
		if (pErrorBlob) {

			//文字列をデバッガに送る
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();
	return S_OK;
}

//
// 入力アセンブラーステージに入力レイアウトオブジェクトをバインドする
//
void Shader::BindInputLayout(ID3D11DeviceContext* pDeviceContext) {
	pDeviceContext->IASetInputLayout(pVertexLayout);
}