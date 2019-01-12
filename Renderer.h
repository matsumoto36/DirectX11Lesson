#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>
#include <iostream>

#include <vector>

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// �`�悷��N���X�̋��ʕ���
//
class Renderer {

protected:

	static ID3D11Device* _device;
	static vector<reference_wrapper<Renderer>>* _rendererList;	//Render����̎Q��

	ID3D11Buffer*					_vertexBuffer;	//���_�o�b�t�@�̃f�[�^
	ID3D11Buffer*					_indicesBuffer;	//�C���f�b�N�X�o�b�t�@�̃f�[�^
	Material*						_material;		//�}�e���A���̃f�[�^
	XMFLOAT4X4						_transform;		//�`��̍��W�f�[�^ XMMATRIX��x86�n�ŃA���C����8�ɂȂ�炵��

	const Mesh*						_mesh;			//�`�悷�郁�b�V���̃f�[�^

public:

	bool								IsRender;		//�`�悷�邩

protected:
	Renderer() {
		IsRender = true;
		_vertexBuffer = nullptr;
		_indicesBuffer = nullptr;
		SetTransform(XMMatrixIdentity());

		_rendererList->push_back(*this);
	}


public:
	~Renderer() {

		if(_material) delete _material;

		//���X�g����폜
		auto itr = _rendererList->begin();
		while (itr != _rendererList->end()) {
			if (&(*itr).get() == this) {
				itr = _rendererList->erase(itr);
			}
			else {
				itr++;
			}
		}

		//�o�b�t�@�[���\�[�X�̊J��
		if (_vertexBuffer) _vertexBuffer->Release();
		if (_indicesBuffer) _indicesBuffer->Release();
	}

	// getter

	// ���W�s���ϊ����Ď擾����
	XMMATRIX GetTransform() const {
		return XMLoadFloat4x4(&_transform);
	}

	// ���W�s���ϊ����ăZ�b�g����
	void SetTransform(const XMMATRIX transform) {
		XMStoreFloat4x4(&_transform, transform);
	}

	ID3D11Buffer* & GetVertexBuffer() {
		return _vertexBuffer;
	}

	ID3D11Buffer* & GetIndexBuffer() {
		return _indicesBuffer;
	}

	const class Material* GetMaterial() const {
		return _material;
	}

	void SetMaterial(Material* const material) {
		if (_material) delete _material;
		_material = material;
	}

	// �v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ�������o�C���h����
	void SetPrimitiveTopology(ID3D11DeviceContext* const context) {
		//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST		���_�f�[�^���O�p�`�̃��X�g�Ƃ��ĉ���(2�̎O�p�`��6�̒��_)
		//D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP	���_�f�[�^���O�p�`�̃X�g���b�v�Ƃ��ĉ���(2�̎O�p�`��4�̒��_
		context->IASetPrimitiveTopology(_mesh->GetPrimitiveTopology());
	}

	// �T�u���\�[�X�̍X�V���ɌĂ΂��
	virtual void OnUpdateSubResource(ID3D11DeviceContext* const context) {}

	// �`�悳���Ƃ��ɌĂ΂��
	virtual void OnDraw(ID3D11DeviceContext* const context) {}

	// �����ɕK�v�ȃf�[�^��ێ����Ă���
	static void SetRenderData(ID3D11Device* const device, vector<reference_wrapper<Renderer>>& rendererList) {
		Renderer::_device = device;
		Renderer::_rendererList = &rendererList;
	}
};

