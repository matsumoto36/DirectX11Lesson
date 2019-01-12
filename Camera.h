#pragma once

#include <DirectXMath.h>
#include <d3d11.h>					//DirectX11

#include "Vector3.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要

using namespace std;
using namespace DirectX;

class Camera {

	//カメラの位置
	XMVECTOR _eye = XMVectorSet(0.0f, 0.0f, -4.0f, 0.0f);
	//カメラの焦点
	XMVECTOR _focus = XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f);
	//現在のワールド座標における上方向の定義
	XMVECTOR _up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	//カメラの視野角
	float _fov;
	//アスペクト比
	float _aspect;
	//ニア(見える範囲の前方)
	float _nearZ;
	//ファー(見える範囲の広報)
	float _farZ;

	//ビュー行列
	XMMATRIX _cameraView;
	//パースペクティブ射影行列
	XMMATRIX _cameraProj;

public:
	Camera(Vector3 position, float aspect) {

		SetPosition(position);
		
		_fov = XMConvertToRadians(45.0f);
		_aspect = aspect; //g_ViewPort.Width / g_ViewPort.Height;
		_nearZ = 0.1f;
		_farZ = 100.0f;

		//視野に基づいて、左手座標系のパースペクティブ射影行列を作成
		_cameraProj = XMMatrixPerspectiveFovLH(_fov, _aspect, _nearZ, _farZ);

	}
	~Camera();

	XMMATRIX GetView() const { return _cameraView; }
	XMMATRIX GetProj() const { return _cameraProj; }

	void SetPosition(Vector3 position) {

		_eye = XMVectorSet(position.x, position.y, position.z, 0.0f);
		_focus = XMVectorSet(position.x, position.y, 0.0f, 0.0f);
		_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

		//カメラの位置、上方向、および焦点を利用して
		//左手座標系のビュー行列を作成
		_cameraView = XMMatrixLookAtLH(_eye, _focus, _up);
	}

	Vector3 GetPosition() const {
		return { XMVectorGetX(_eye), XMVectorGetY(_eye), XMVectorGetZ(_eye) };
	}
};

