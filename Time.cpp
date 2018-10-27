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

	//計測するための時計を選択
	if (QueryPerformanceFrequency(&clockCountFrequency) != 0) {

		//一秒あたりのクロック数を取得
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

	//時間を更新
	TimeUpdate();

	//時間に余裕がある場合
	if (deltaTime < minFrameTime) {

		//寝る時間をミリ秒で計算
		auto sleepTime = static_cast<DWORD>((minFrameTime - deltaTime) * 1000);

		//精度を上げてから寝ないとガバガバ
		timeBeginPeriod(1);
		Sleep(sleepTime);
		timeEndPeriod(1);

		//寝たので時間を更新しておく
		TimeUpdate();

	}

	//余裕がない場合は何もしない

	frameCount++;
	clockCountPrev = clockCount;
}

void Time::TimeUpdate() {

	QueryPerformanceCounter(&clockCount);

	//現在までの時間 = 今の時間 / 周波数
	time = static_cast<double>(clockCount.QuadPart - clockCountAwake.QuadPart)
		/ static_cast<double>(clockCountFrequency.QuadPart);

	//フレーム間時間 = (今の時間 - 前フレームの時間) / 周波数
	deltaTime = static_cast<double>(clockCount.QuadPart - clockCountPrev.QuadPart)
		/ static_cast<double>(clockCountFrequency.QuadPart);

	//FPSの更新
	if (deltaTime > 0.0f) {
		fps = 1.0f / deltaTime;
	}
}