#include "Time.h"

bool Time::isInitialized = false;

long Time::frameCount = 0;
float Time::deltaTime = 0.02f;
float Time::time = 0.0f;

float Time::fps;
float Time::minFrameTime;

LARGE_INTEGER Time::clockCountAwake;
LARGE_INTEGER Time::clockCountPrev;
LARGE_INTEGER Time::clockCount;
LARGE_INTEGER Time::clockCountFrequency;


bool Time::Init(float fps) {

	//�v�����邽�߂̎��v��I��
	if (QueryPerformanceFrequency(&clockCountFrequency) != 0) {

		//��b������̃N���b�N�����擾
		QueryPerformanceCounter(&clockCountAwake);
		clockCountPrev = clockCountAwake;

		SetFPS(fps);

		isInitialized = true;
	}
	else {

		std::cout << TEXT("Failed Initialize Time.") << std::endl;

	}

	return isInitialized;
}

void Time::Update() {

	if (!isInitialized) return;

	//���Ԃ��X�V
	TimeUpdate();

	//���Ԃɗ]�T������ꍇ
	if (deltaTime < minFrameTime) {

		//�Q�鎞�Ԃ��~���b�Ōv�Z
		auto sleepTime = static_cast<DWORD>((minFrameTime - deltaTime) * 1000);

		//���x���グ�Ă���Q�Ȃ��ƃK�o�K�o
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);

		//�Q���̂Ŏ��Ԃ��X�V���Ă���
		TimeUpdate();

	}

	//�]�T���Ȃ��ꍇ�͉������Ȃ�

	frameCount++;
	clockCountPrev = clockCount;
}

void Time::TimeUpdate() {

	QueryPerformanceCounter(&clockCount);

	//���݂܂ł̎��� = ���̎��� / ���g��
	time = static_cast<double>(clockCount.QuadPart - clockCountAwake.QuadPart)
		/ static_cast<double>(clockCountFrequency.QuadPart);

	//�t���[���Ԏ��� = (���̎��� - �O�t���[���̎���) / ���g��
	deltaTime = static_cast<double>(clockCount.QuadPart - clockCountPrev.QuadPart)
		/ static_cast<double>(clockCountFrequency.QuadPart);

	//FPS�̍X�V
	if (deltaTime > 0.0f) {
		fps = 1.0f / deltaTime;
	}
}