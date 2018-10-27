#pragma once

#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

//
// ���Ԃ��v������AUpdate�����肳����N���X
//
class Time final {


	static bool isInitialized;					//�������ł�����
	
	static long frameCount;						//���݂܂ł̃t���[���o�ߐ�
	static float deltaTime;						//�t���[���Ԏ���
	static float time;							//���݂܂ł̌o�ߎ���
	
	static float fps;							//Frame per Seconds
	static float minFrameTime;					//�ڕW�ƂȂ鏈������

	static LARGE_INTEGER clockCountAwake;		//�N�����̃N���b�N�J�E���g��
	static LARGE_INTEGER clockCountPrev;		//1�t���[���O�̃N���b�N�J�E���g��
	static LARGE_INTEGER clockCount;			//1�t���[���̃N���b�N�J�E���g��
	static LARGE_INTEGER clockCountFrequency;	//�N���b�N���̐��x


public:

	static bool Init(float fps);

	// ���������Ă���̌o�߃t���[�����擾����
	static long GetFrameCount() {
		return frameCount;
	}

	// �t���[���Ԏ��Ԃ��擾����
	static float GetDeltaTime() {
		return deltaTime;
	}

	// ���������Ă���̌o�ߎ��Ԃ��擾����
	static float GetTime() {
		return time;
	}

	// FPS���擾����
	static float GetFPS() {
		return fps;
	}

	// FPS�̐ݒ�
	// vsync�̖W�Q���󂯂�
	static void SetFPS(float fps) {
		minFrameTime = 1.0f / fps;
	}

	// ���Ԃ��X�V���A���FPS����邽�߂�sleep����
	static void Update();

private:

	// ���Ԃ݂̂��X�V����
	static void TimeUpdate();
};

