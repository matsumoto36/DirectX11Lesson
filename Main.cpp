
//�K�v�ȃw�b�_�[���C���N���[�h
#include <Windows.h>				//Windows�v���O�����Œʏ�K�v�ƂȂ�w�b�_�t�@�C��

#include "Render.h"
#include "Shader.h"
#include "Mesh.h"
#include "Time.h"
#include "ControlObject.h"

//std. ���^�C�v����̂��ȗ�����
using namespace std;
using namespace DirectX;



//
// Win32 �A�v���P�[�V�����̏����G���g���|�C���g
// 
// �p�����[�^
// HINSTANCE  ���݂̃C���X�^���X�̃n���h��
// HINSTANCE  �ȑO�̃C���X�^���X�̃n���h��
// LPSTR      �R�}���h���C��
// int        �\�����
//
// �߂�l
// �I���R�[�h
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//�E�B���h�E�̏�����
	if (FAILED(Render::Init(hInstance, nCmdShow, "DirectX Lesson"))) {
		return 0;
	}

	//�^�C�}�[��60fps�ŏ�����
	Time::Init(60);

	auto obj = new ControlObject();
	obj->Start();

	//���b�Z�[�W�̍\����
	MSG hMsg = {};

	//�\���̂̏�����
	ZeroMemory(&hMsg, sizeof(hMsg));

	//��{���[�v
	while (hMsg.message != WM_QUIT) {

		    //���b�Z�[�W���d�����Ȃ��悤�ɑ��M���Č��ʂ��󂯎��
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			//���b�Z�[�W���󂯎�����ꍇ
			
			TranslateMessage(&hMsg);	//���b�Z�[�W�𕶎����b�Z�[�W�֕ϊ�
			DispatchMessage(&hMsg);		//�E�B���h�E�v���V�[�W���փ��b�Z�[�W�𑗐M
		}
		else {
			//���b�Z�[�W���󂯎��Ȃ������ꍇ//

			//�`����R���g���[������I�u�W�F�N�g�̃A�b�v�f�[�g
			obj->Update();
			//���삳�ꂽ�|���S����`��
			Render::Rendering();
			//FPS�̈ێ�
			Time::Update();
		}
	}

	if (obj) delete obj;

	//�f�o�C�X�ƃX���b�v�`�F�C���̊J��
	Render::CleanupDevice();

	return 0;
}