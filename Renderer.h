#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>
#include <iostream>

#include <vector>

#include "Shader.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// �`�悷��N���X�̋��ʕ���
//
class Renderer {

protected:

	static ID3D11Device* device;
	static vector<reference_wrapper<Renderer>>* rendererList;	//Render����̎Q��

public:

	bool						isRender;		//�`�悷�邩
	XMMATRIX					transform;		//�`��̍��W�f�[�^
	ID3D11Buffer*				pVertexBuffer;	//���_�o�b�t�@�[�̃f�[�^
	ID3D11VertexShader*			pVertexShader;	//���_�V�F�[�_�[
	ID3D11PixelShader*			pPixelShader;	//�s�N�Z���V�F�[�_�[

protected:
	Renderer() {
		isRender = true;
		rendererList->push_back(*this);
	}


public:
	~Renderer() {

		//���X�g����폜
		auto itr = rendererList->begin();
		while (itr != rendererList->end()) {
			if (&(*itr).get() == this) {
				itr = rendererList->erase(itr);
			}
			else {
				itr++;
			}
		}

		//�o�b�t�@�[���\�[�X�̊J��
		if (pVertexBuffer) pVertexBuffer->Release();
	}

	// �T�u���\�[�X�̍X�V���ɌĂ΂��
	virtual void UpdateSubResource(ID3D11DeviceContext* const context) {}

	// �V�F�[�_�[�̃Z�b�g��ɌĂ΂��
	virtual void SetShaderResources(ID3D11DeviceContext* const context) {}

	// �`�悳���Ƃ��ɌĂ΂��
	virtual void Draw(ID3D11DeviceContext* const context) {}

	// �V�F�[�_�[��ݒ肷��
	void SetShader(wstring name) {
		//�V�F�[�_�[���擾
		Shader::GetShader(name, pVertexShader, pPixelShader);
	}


	// �����ɕK�v�ȃf�[�^��ێ����Ă���
	static void SetRenderData(ID3D11Device* device, vector<reference_wrapper<Renderer>>& rendererList) {
		Renderer::device = device;
		Renderer::rendererList = &rendererList;
	}
};

