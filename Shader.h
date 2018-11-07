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
#include "FileAccess.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;

//
// �V�F�[�_�[��ǂݍ���ŊǗ�����N���X
//
class Shader final {

	static ID3D11InputLayout*	pVertexLayout;			//���̓A�Z���u���[�X�e�[�W�̓��̓f�[�^�ɃA�N�Z�X
	static D3D11_INPUT_ELEMENT_DESC vertexDesc[];		//�����ɒ�`�������e�����_�V�F�[�_�[�ɑ�����
	static vector<wstring> shaderNameList;				//�ǂݍ��܂�Ă���V�F�[�_�[�̃��X�g

private:
	Shader();

public:

	static unordered_map<wstring, ID3D11VertexShader*>	pVertexShaderMap;	//���_�V�F�[�_�[�X�e�[�W�𐧌䂷����s�\�v���O���� (���_�V�F�[�_�[) ���Ǘ�
	static unordered_map<wstring, ID3D11PixelShader*>	pPixelShaderMap;	//�s�N�Z���V�F�[�_�[�X�e�[�W�𐧌䂷����s�\�v���O���� (�s�N�Z�� �V�F�[�_�[) ���Ǘ�

	static HRESULT Initialize(ID3D11Device* device);
	static void Finalize();

	// ���O���w�肵�ăV�F�[�_�[���擾����
	static void GetShader(wstring name, ID3D11VertexShader* &pVertexShader, ID3D11PixelShader* &pPixelShader);

	// ���̖��O�̃V�F�[�_�[�����݂��Ă��邩���ׂ�
	static bool IsValidShader(wstring name);

	// ���_�V�F�[�_�[�̍쐬
	static HRESULT CreateVertexShader(ID3D11Device* device, const wchar_t* vs, ID3D11VertexShader* &pVertexShader);
	// �s�N�Z���V�F�[�_�[�̍쐬
	static HRESULT CreatePixelShader(ID3D11Device* device, const wchar_t* ps, ID3D11PixelShader* &pPixelShader);

	// �t�@�C�����w�肵�ăV�F�[�_�[���R���p�C������
	static HRESULT CompileShaderFromFile(WCHAR* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3DBlob** ppBlobOut);

	// ���̓A�Z���u���[�X�e�[�W�ɓ��̓��C�A�E�g�I�u�W�F�N�g���o�C���h����
	static void BindInputLayout(ID3D11DeviceContext* pDeviceContext);
};

