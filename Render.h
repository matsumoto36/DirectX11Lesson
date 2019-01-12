#pragma once

//�K�v�ȃw�b�_�[���C���N���[�h
#include <tchar.h>					//Microsoft�ŗL�̔ėp�e�L�X�g�̃}�b�s���O
#include <Windows.h>				//Windows�v���O�����Œʏ�K�v�ƂȂ�w�b�_�t�@�C��
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>

#include "Camera.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "ControlObject.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

//std. ���^�C�v����̂��ȗ�����
using namespace std;
using namespace DirectX;

//
// �����_���ɏ]���ĕ`����s���N���X
//
class Render final {

	//�`�悷�郌���_���̃��X�g
	static vector<reference_wrapper<Renderer>> rendererList;

	static Camera*					_camera;

	//�E�B���h�E�T�C�Y
	static int windowSizeX;
	static int windowSizeY;

	//�E�B���h�E�I�u�W�F�N�g
	static HWND g_hWnd;

	static D3D_FEATURE_LEVEL		g_pFeatureLevels[];			//�f�o�C�X�̋@�\���x���̃��X�g���`
		
	static UINT						g_FeatureLevels;			//�^�[�Q�b�g�̗v�f��
	static D3D_FEATURE_LEVEL		g_FeatureLevelsSupported;	//�f�o�C�X�쐬���ɕԂ����o�[�W����

	static ID3D11Device*			g_pd3dDevice;				//�����_�����O�y�у��\�[�X�̍쐬�Ɏg�p
	static ID3D11DeviceContext*		g_pImmedicateContext;		//�����_�����O�R�}���h�𐶐�����f�o�C�X�R�}���h
	static IDXGISwapChain*			g_pSwapChain;				//�����_�����O�f�[�^��\���O�Ɋi�[����
	static ID3D11RenderTargetView*	g_pRenderTargetView;		//�����_�����O���Ƀ����_�[�^�[�Q�b�g�̃T�u���\�[�X������
	static D3D11_VIEWPORT			g_ViewPort;					//�r���[�|�[�g�̐��@���`
	static ID3D11Texture2D*			g_pDepthStencil;			//�[�x�E�X�e���V�����\�[�X�Ƃ��Ďg�p
	static ID3D11DepthStencilView*	g_pDepthStencilView;		//�[�x�E�X�e���V�����\�[�X�ɃA�N�Z�X����

	static ID3D11BlendState*		g_pBlendState;				//�A���t�@�u�����h
	static ID3D11RasterizerState*	g_pRasterizerState;			//���X�^���C�U�[

	static ID3D11SamplerState*		g_pSamplerState;			//�e�N�X�`���̃T���v���[�X�e�[�g

public:

private:
	Render();

public:
	
	static HRESULT Init(HINSTANCE hInstance, int nCmdShow, const string& windowName);
	static void CleanupDevice();					//�f�o�C�X�ƃX���b�v�`�F�C���̊J��
	static Camera& GetCamera() { return *_camera; }
	static void Rendering();						//�`����s��

private:

	static void InitWindow(HINSTANCE hInstance, const string& windowName);
	static HRESULT InitDevice();					//�f�o�C�X�ƃX���b�v�`�F�C���̏�����
	static void RenderClear();						//�`�������

};