#include "Shader.h"

vector<vector<D3D11_INPUT_ELEMENT_DESC>> Shader::_inputLayoutDescList;

D3D11_INPUT_ELEMENT_DESC Shader::vertexDesc[] {
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
};

vector<GeneratedShader*> Shader::loadedShaderList;

HRESULT Shader::Initialize(ID3D11Device &device) {

	//�J�����g�f�B���N�g������A�ǂݍ��ރV�F�[�_�[�̃f�B���N�g�����擾
	wchar_t cdir[255];
	GetCurrentDirectoryW(255, cdir);
	wstring currntDirectory = cdir;

	vector<wstring> directories;
	FileAccess::SearchDirectoryPathInDirectory(currntDirectory + L"\\Shader\\*", directories);

	//�V�F�[�_�[���쐬
	for (auto item : directories) {


		ID3D11PixelShader* pixelShader = nullptr;
		ID3D11ShaderReflection* pixelShaderReflection = nullptr;

		auto basePath = L"Shader/";
		auto vertexShaderFileName = basePath + item + L"/VertexShader.hlsl";
		auto pixelShaderFileName = basePath + item + L"/PixelShader.hlsl";

		try {
			HRESULT hr;
			
			//�V�F�[�_�[�̍쐬
			ID3D11VertexShader* vertexShader = nullptr;
			ID3D11InputLayout* inputLayout = nullptr;
			ID3D11ShaderReflection* vertexShaderReflection = nullptr; 
			hr = CreateVertexShader(device, (vertexShaderFileName).c_str(), vertexShader, inputLayout, vertexShaderReflection);
			if(FAILED(hr)) throw hr;
			hr = CreatePixelShader(device, (pixelShaderFileName).c_str(), pixelShader, pixelShaderReflection);
			if (FAILED(hr)) throw hr;
	
			loadedShaderList.push_back(new GeneratedShader(
				item,
				vertexShader,
				inputLayout,
				pixelShader,
				vector<ShaderVariable*> {//ShaderStage�̏��ɓ����
					new ShaderVariable(device, *vertexShaderReflection),
					new ShaderVariable(device, *pixelShaderReflection)
				}
			));
		}
		catch (int error) {

			cout << item.c_str() << "�V�F�[�_�[���ǂݍ��߂܂���ł���" << endl;

		}


	}

	return S_OK;
}

void Shader::Finalize() {

	//�V�F�[�_�[���J��
	for (size_t i = 0; i < loadedShaderList.size(); i++) {
		if (loadedShaderList[i]) delete loadedShaderList[i];
	}

	loadedShaderList.clear();

	//���̓��C�A�E�g�̊J��
	//if (pVertexLayout) pVertexLayout->Release();
}

bool Shader::FindShader(const wstring name, const ID3D11VertexShader* &vertexShader, const ID3D11PixelShader* &pixelShader) {

	auto asset = FindShader(name);
	if (asset) {
		vertexShader = asset->GetVertexShader();
		pixelShader = asset->GetPixelShader();
	}

	return asset;
}

const GeneratedShader* const Shader::FindShader(const wstring &name) {

	for (auto item : loadedShaderList) {
		if (item->GetName() == name) return item;
	}

	return nullptr;
}

HRESULT Shader::CreateVertexShader(ID3D11Device &device, const wchar_t* vs, ID3D11VertexShader* &vertexShader, ID3D11InputLayout* &inputLayout, ID3D11ShaderReflection* &reflection) {
	
	ID3DBlob* pVSBlob = nullptr;
	auto hr = S_OK;

	//���_�V�F�[�_�[���R���p�C��
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)vs,
		"main",
		"vs_4_0",
		&pVSBlob
	);

	//���t���N�V�����f�[�^���i�[
	hr = D3DReflect(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
	if (FAILED(hr)) return E_FAIL;

	//���_�V�F�[�_�[���쐬
	hr = device.CreateVertexShader(
		pVSBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
		pVSBlob->GetBufferSize(),		//�R���p�C���ςݒ��_�V�F�[�_�[�̃T�C�Y
		nullptr,						//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^
		&vertexShader				//ID3D11VertexShader �C���^�[�t�F�C�X�ւ̃|�C���^
	);

	if (FAILED(hr)) return E_FAIL;

	//���̓��C�A�E�g�̍쐬
	D3D11_SHADER_DESC shaderDesc;
	reflection->GetDesc(&shaderDesc);
	vector<D3D11_INPUT_ELEMENT_DESC> inputLayoutDescList;

	for (size_t i = 0; i < shaderDesc.InputParameters; i++) {

		D3D11_SIGNATURE_PARAMETER_DESC sigdesc;
		reflection->GetInputParameterDesc(i, &sigdesc);

		auto format = GetDxgiFormat(sigdesc.ComponentType, sigdesc.Mask);

		D3D11_INPUT_ELEMENT_DESC desc = {
			sigdesc.SemanticName,
			sigdesc.SemanticIndex,
			format,
			0,
			D3D11_APPEND_ALIGNED_ELEMENT,
			D3D11_INPUT_PER_VERTEX_DATA,
			0 };

		inputLayoutDescList.push_back(desc);
	}

	_inputLayoutDescList.push_back(inputLayoutDescList);
	/*
	D3D11_INPUT_ELEMENT_DESC Shader::vertexDesc[]{
	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "COLOR",		0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	D3D11_APPEND_ALIGNED_ELEMENT,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
};
*/
	//inputLayoutDescList.data();

	//hr = device.CreateInputLayout(
	//	&inputLayoutDescList[0],			//���̓A�Z���u���[�X�e�[�W�̓��̓f�[�^�^�̔z��
	//	inputLayoutDescList.size(),			//���͗v�f�̔z����̓��̓f�[�^�^�̐�
	//	pVSBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
	//	pVSBlob->GetBufferSize(),		//�R���p�C���ςݒ��_�V�F�[�_�[�̃T�C�Y
	//	&inputLayout				//�쐬�������̓��C�A�E�g �I�u�W�F�N�g�ւ̃|�C���^
	//);

	//hr = device.CreateInputLayout(
	//	&_inputLayoutDescList[_inputLayoutDescList.size() - 1][0],			//���̓A�Z���u���[�X�e�[�W�̓��̓f�[�^�^�̔z��
	//	inputLayoutDescList.size(),			//���͗v�f�̔z����̓��̓f�[�^�^�̐�
	//	pVSBlob->GetBufferPointer(),	//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
	//	pVSBlob->GetBufferSize(),		//�R���p�C���ςݒ��_�V�F�[�_�[�̃T�C�Y
	//	&inputLayout					//�쐬�������̓��C�A�E�g �I�u�W�F�N�g�ւ̃|�C���^
	//);

	//���̃R�[�h�͓��삷��
	hr = device.CreateInputLayout(
		vertexDesc,					
		ARRAYSIZE(vertexDesc),		
		pVSBlob->GetBufferPointer(),
		pVSBlob->GetBufferSize(),	
		&inputLayout				
	);

	pVSBlob->Release();

	return hr;
}


HRESULT Shader::CreatePixelShader(ID3D11Device &device, const wchar_t* ps, ID3D11PixelShader* &pixelShader, ID3D11ShaderReflection* &reflection) {

	ID3DBlob* pPSBlob = nullptr;
	auto hr = S_OK;

	//�s�N�Z���V�F�[�_�[���R���p�C��
	hr = Shader::CompileShaderFromFile(
		(wchar_t*)ps,
		"main",
		"ps_4_0",
		&pPSBlob
	);

	//���t���N�V�����f�[�^���i�[
	hr = D3DReflect(pPSBlob->GetBufferPointer(), pPSBlob->GetBufferSize(), IID_ID3D11ShaderReflection, (void**)&reflection);
	if (FAILED(hr)) return E_FAIL;

	//�s�N�Z���V�F�[�_�[�̍쐬
	hr = device.CreatePixelShader(
		pPSBlob->GetBufferPointer(),		//�R���p�C���ς݃V�F�[�_�[�ւ̃|�C���^
		pPSBlob->GetBufferSize(),			//�R���p�C���ς݃s�N�Z���V�F�[�_�[�̃T�C�Y
		nullptr,							//�N���X�����N�C���^�[�t�F�C�X�ւ̃|�C���^
		&pixelShader						//ID3D11PixelShader �C���^�[�t�F�C�X�ւ̃|�C���^
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
	hr = D3DCompileFromFile(szFileName, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, szEntryPoint, szShaderModel,
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

DXGI_FORMAT Shader::GetDxgiFormat(D3D10_REGISTER_COMPONENT_TYPE type, BYTE mask) {
	if ((mask & 0x0F) == 0x0F) {
		// xyzw
		switch (type) {
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32B32A32_FLOAT;
		}
	}

	if ((mask & 0x07) == 0x07) {
		// xyz
		switch (type) {
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32B32_FLOAT;
		}
	}

	if ((mask & 0x03) == 0x03) {
		// xy
		switch (type) {
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32G32_FLOAT;
		}
	}

	if ((mask & 0x1) == 0x1) {
		// x
		switch (type) {
			case D3D10_REGISTER_COMPONENT_FLOAT32:
				return DXGI_FORMAT_R32_FLOAT;
		}
	}

	return DXGI_FORMAT_UNKNOWN;
}
