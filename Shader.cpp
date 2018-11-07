#include "Shader.h"

ID3D11InputLayout*							Shader::pVertexLayout = nullptr;

D3D11_INPUT_ELEMENT_DESC Shader::vertexDesc[]{
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,								D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
};

vector<wstring> Shader::shaderNameList;

unordered_map<wstring, ID3D11VertexShader*>	Shader::pVertexShaderMap;
unordered_map<wstring, ID3D11PixelShader*>	Shader::pPixelShaderMap;


HRESULT Shader::Initialize(ID3D11Device* device) {

	//�J�����g�f�B���N�g������A�ǂݍ��ރV�F�[�_�[�̃f�B���N�g�����擾
	wchar_t cdir[255];
	GetCurrentDirectoryW(255, cdir);
	wstring currntDirectory = cdir;

	vector<wstring> directories;
	FileAccess::SearchDirectoryPathInDirectory(currntDirectory + L"\\Shader\\*", directories);

	//�V�F�[�_�[���쐬
	for (auto item : directories) {

		pVertexShaderMap.emplace(item, nullptr);
		pPixelShaderMap.emplace(item, nullptr);

		auto basePath = L"Shader/";
		auto vertexShaderFileName = basePath + item + L"/VertexShader.hlsl";
		auto pixelShaderFileName = basePath + item + L"/PixelShader.hlsl";

		try {
			HRESULT hr;
			
			hr = CreateVertexShader(device, (vertexShaderFileName).c_str(), pVertexShaderMap[item]);
			if(FAILED(hr)) throw hr;
			hr = CreatePixelShader(device, (pixelShaderFileName).c_str(), pPixelShaderMap[item]);
			if (FAILED(hr)) throw hr;

			shaderNameList.push_back(item);
		}
		catch (int error) {

			pVertexShaderMap.erase(item);
			pPixelShaderMap.erase(item);

			cout << item.c_str() << "�V�F�[�_�[���ǂݍ��߂܂���ł���" << endl;

		}


	}

	return S_OK;
}

void Shader::Finalize() {

	//�V�F�[�_�[���J��
	for (auto item : shaderNameList) {
		if (pVertexShaderMap[item]) delete pVertexShaderMap[item];
		if (pPixelShaderMap[item]) delete pPixelShaderMap[item];
	}

	shaderNameList.clear();
	pVertexShaderMap.clear();
	pPixelShaderMap.clear();

	//���̓��C�A�E�g�̊J��
	if (pVertexLayout) pVertexLayout->Release();
}

void Shader::GetShader(wstring name, ID3D11VertexShader* &pVertexShader, ID3D11PixelShader* &pPixelShader) {

	if (!IsValidShader(name)) return;

	pVertexShader = pVertexShaderMap[name];
	pPixelShader = pPixelShaderMap[name];
}

bool Shader::IsValidShader(wstring name) {

	for (auto item : shaderNameList) {
		if (item == name) return true;
	}

	return false;
}

HRESULT Shader::CreateVertexShader(ID3D11Device* device, const wchar_t* vs, ID3D11VertexShader* &pVertexShader) {
	
	ID3DBlob* pVSBlob = nullptr;
	auto hr = S_OK;

	//���_�V�F�[�_�[���R���p�C��
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)vs,
		"main",
		"vs_4_0",
		&pVSBlob
	);

	//���_�V�F�[�_�[���쐬
	hr = device->CreateVertexShader(
		pVSBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
		pVSBlob->GetBufferSize(),		//�R���p�C���ςݒ��_�V�F�[�_�[�̃T�C�Y
		nullptr,						//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^
		&pVertexShader				//ID3D11VertexShader �C���^�[�t�F�C�X�ւ̃|�C���^
	);

	if (FAILED(hr)) return E_FAIL;

	//���̓��C�A�E�g���쐬
	hr = device->CreateInputLayout(
		vertexDesc,					//���̓A�Z���u���[�X�e�[�W�̓��̓f�[�^�^�̔z��
		ARRAYSIZE(vertexDesc),		//���͗v�f�̔z����̓��̓f�[�^�^�̐�
		pVSBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
		pVSBlob->GetBufferSize(),		//�R���p�C���ςݒ��_�V�F�[�_�[�̃T�C�Y
		&pVertexLayout				//�쐬�������̓��C�A�E�g �I�u�W�F�N�g�ւ̃|�C���^
	);
	pVSBlob->Release();

	return hr;
}


HRESULT Shader::CreatePixelShader(ID3D11Device* device, const wchar_t* ps, ID3D11PixelShader* &pPixelShader) {

	ID3DBlob* pPSBlob = nullptr;
	auto hr = S_OK;

	//�s�N�Z���V�F�[�_�[���R���p�C��
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)ps,
		"main",
		"ps_4_0",
		&pPSBlob
	);

	//�s�N�Z���V�F�[�_�[�̍쐬
	hr = device->CreatePixelShader(
		pPSBlob->GetBufferPointer(),		//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
		pPSBlob->GetBufferSize(),			//�R���p�C���ς݃s�N�Z���V�F�[�_�[�̃T�C�Y
		nullptr,							//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^
		&pPixelShader						//ID3D11PixelShader �C���^�[�t�F�C�X�ւ̃|�C���^
	);
	pPSBlob->Release();

	return hr;
}

HRESULT Shader::CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut) {

	HRESULT hr = S_OK;

	//�R���p�C����HLSL�R�[�h���R���p�C��������@���w��
	DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;	//�����ȃR���p�C��������

	#ifdef _DEBUG
	dwShaderFlags |= D3DCOMPILE_DEBUG;					//�f�o�b�O�����R�[�h�ɑ}������
	dwShaderFlags |= D3DCOMPILE_SKIP_OPTIMIZATION;		//�œK���X�e�b�v���X�L�b�v����

	#endif // DEBUG

														//�R���p�C����̃o�C�i���f�[�^���i�[����ϐ�
	ID3DBlob* pErrorBlob = nullptr;

	//�t�@�C������V�F�[�_�[���R���p�C��
	hr = D3DCompileFromFile(szFileName, nullptr, nullptr, szEntryPoint, szShaderModel,
		dwShaderFlags, 0, ppBlobOut, &pErrorBlob);

	if (FAILED(hr)) {
		if (pErrorBlob) {

			//��������f�o�b�K�ɑ���
			OutputDebugStringA(reinterpret_cast<const char*>(pErrorBlob->GetBufferPointer()));
			pErrorBlob->Release();
		}
		return hr;
	}
	if (pErrorBlob) pErrorBlob->Release();
	return S_OK;
}

void Shader::BindInputLayout(ID3D11DeviceContext* pDeviceContext) {
	pDeviceContext->IASetInputLayout(pVertexLayout);
}