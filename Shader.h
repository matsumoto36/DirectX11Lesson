#pragma once

#include <tchar.h>					//Microsoft�ŗL�̔ėp�e�L�X�g�̃}�b�s���O
#include <Windows.h>				//Windows�v���O�����Œʏ�K�v�ƂȂ�w�b�_�t�@�C��
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>
#include <iostream>

#include <unordered_map>			//�V�F�[�_�[���Ǘ����邽�߂ɗ��p
#include <string>
#include <corecrt_wstring.h>

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;

//
// �V�F�[�_�[��ǂݍ���ŊǗ�����N���X
//
class Shader final {

	static ID3D11InputLayout*	pVertexLayout;			//���̓A�Z���u���[�X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X
	static D3D11_INPUT_ELEMENT_DESC vertexDesc[];		//�����ɒ�`�������e�����_�V�F�[�_�[�ɑ�����

private:
	Shader();

public:

	static unordered_map<wstring, ID3D11VertexShader*>	pVertexShaderMap;	//���_�V�F�[�_�[�X�e�[�W�𐧌䂷����s�\�v���O���� (���_�V�F�[�_�[) ���Ǘ�
	static unordered_map<wstring, ID3D11PixelShader*>	pPixelShaderMap;	//�s�N�Z���V�F�[�_�[�X�e�[�W�𐧌䂷����s�\�v���O���� (�s�N�Z�� �V�F�[�_�[) ���Ǘ�

	static HRESULT Initialize(ID3D11Device* device);
	static void Finalize();

	static void GetShader(wstring name, ID3D11VertexShader* &pVertexShader, ID3D11PixelShader* &pPixelShader);

	static HRESULT CreateVertexShader(ID3D11Device* device, const wchar_t* vs, ID3D11VertexShader* &pVertexShader);
	static HRESULT CreatePixelShader(ID3D11Device* device, const wchar_t* ps, ID3D11PixelShader* &pPixelShader);

	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	static void BindInputLayout(ID3D11DeviceContext* pDeviceContext);
};

