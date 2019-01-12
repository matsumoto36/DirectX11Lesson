#pragma once

#include <DirectXMath.h>
#include <d3d11.h>					//DirectX11

#include "Vector3.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v

using namespace std;
using namespace DirectX;

class Camera {

	//�J�����̈ʒu
	XMVECTOR _eye = XMVectorSet(0.0f, 0.0f, -4.0f, 0.0f);
	//�J�����̏œ_
	XMVECTOR _focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//���݂̃��[���h���W�ɂ����������̒�`
	XMVECTOR _up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//�J�����̎���p
	float _fov;
	//�A�X�y�N�g��
	float _aspect;
	//�j�A(������͈͂̑O��)
	float _nearZ;
	//�t�@�[(������͈͂̍L��)
	float _farZ;

	//�r���[�s��
	XMMATRIX _cameraView;
	//�p�[�X�y�N�e�B�u�ˉe�s��
	XMMATRIX _cameraProj;

public:
	Camera(Vector3 position, float aspect) {

		SetPosition(position);
		
		_fov = XMConvertToRadians(45.0f);
		_aspect = aspect; //g_ViewPort.Width / g_ViewPort.Height;
		_nearZ = 0.1f;
		_farZ = 100.0f;

		//����Ɋ�Â��āA������W�n�̃p�[�X�y�N�e�B�u�ˉe�s����쐬
		_cameraProj = XMMatrixPerspectiveFovLH(_fov, _aspect, _nearZ, _farZ);

	}
	~Camera();

	XMMATRIX GetView() const { return _cameraView; }
	XMMATRIX GetProj() const { return _cameraProj; }

	void SetPosition(Vector3 position) {

		_eye = XMVectorSet(position.x, position.y, position.z, 0.0f);
		_focus = XMVectorSet(position.x, position.y, 0.0f, 0.0f);
		_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//�J�����̈ʒu�A������A����яœ_�𗘗p����
		//������W�n�̃r���[�s����쐬
		_cameraView = XMMatrixLookAtLH(_eye, _focus, _up);
	}

	Vector3 GetPosition() const {
		return { XMVectorGetX(_eye), XMVectorGetY(_eye), XMVectorGetZ(_eye) };
	}
};

