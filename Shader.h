#pragma once

#include <tchar.h>					//Microsoft�ŗL�̔ėp�e�L�X�g�̃}�b�s���O
#include <Windows.h>				//Windows�v���O�����Œʏ�K�v�ƂȂ�w�b�_�t�@�C��
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>
#include <iostream>

#include <array>

#include <string>
#include <corecrt_wstring.h>
#include "FileAccess.h"
#include "ShaderVariable.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;

enum class ShaderStage;
class GeneratedShader;

//
// �V�F�[�_�[��ǂݍ���ŊǗ�����N���X
//
class Shader final {
public:

	static const size_t ShaderStageSize = 2;

private:

	static vector<vector<D3D11_INPUT_ELEMENT_DESC>> _inputLayoutDescList;

	static D3D11_INPUT_ELEMENT_DESC vertexDesc[];		//�����ɒ�`�������e�����_�V�F�[�_�[�ɑ�����

	static vector<GeneratedShader*> loadedShaderList;		//�ǂݍ��܂�Ă���V�F�[�_�[�̃��X�g

private:
	Shader();

public:

	static HRESULT Initialize(ID3D11Device &);
	static void Finalize();

	// ���O���w�肵�ăV�F�[�_�[���擾����
	static bool FindShader(const wstring, const ID3D11VertexShader* &, const ID3D11PixelShader* &);
	static const GeneratedShader* const FindShader(const wstring &);

	// �t�@�C�����w�肵�ăV�F�[�_�[���R���p�C������
	static HRESULT CompileShaderFromFile(WCHAR*, LPCSTR, LPCSTR, ID3DBlob**);

private:
	// ���_�V�F�[�_�[�̍쐬
	static HRESULT CreateVertexShader(ID3D11Device &, const wchar_t*, ID3D11VertexShader* &, ID3D11InputLayout* &, ID3D11ShaderReflection* &);
	// �s�N�Z���V�F�[�_�[�̍쐬
	static HRESULT CreatePixelShader(ID3D11Device &, const wchar_t*, ID3D11PixelShader* &, ID3D11ShaderReflection* &);

	//
	static DXGI_FORMAT GetDxgiFormat(D3D10_REGISTER_COMPONENT_TYPE, BYTE);

};

//
// �V�F�[�_�[�̃X�e�[�W��
//
enum class ShaderStage {
	Vertex,
	Pixel,
};

//
// �V�F�[�_�[�̃f�[�^�A�Z�b�g
//
class GeneratedShader {

	wstring _name;

	ID3D11VertexShader* _vertexShader;
	ID3D11InputLayout* _inputLayout;

	ID3D11PixelShader* _pixelShader;

	vector<ShaderVariable*> _shaderVariables;

public:

	GeneratedShader(
		wstring name,
		ID3D11VertexShader* vertexShader,
		ID3D11InputLayout* inputLayout,
		ID3D11PixelShader* pixelShader,
		vector<ShaderVariable*> ShaderVariables
	) :
		_name(name),
		_vertexShader(vertexShader),
		_inputLayout(inputLayout),
		_pixelShader(pixelShader),
		_shaderVariables(ShaderVariables) {}

	~GeneratedShader() {
		if (_vertexShader) _vertexShader->Release();
		if (_inputLayout) _inputLayout->Release();
		if (_pixelShader) _pixelShader->Release();

		for (auto variable : _shaderVariables) {
			if (variable) delete variable;
		}
	}

	// getter
	const wstring GetName() const {
		return _name;
	}

	ID3D11VertexShader* const GetVertexShader() const {
		return _vertexShader;
	}

	ID3D11InputLayout* const GetInputLayout() const {
		return _inputLayout;
	}

	ID3D11PixelShader* const GetPixelShader() const {
		return _pixelShader;
	}

	vector<ShaderVariable*> const GetVertexShaderVariables() const {
		return _shaderVariables;
	}
};