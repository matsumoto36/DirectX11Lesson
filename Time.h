#pragma once

#include <iostream>
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

using namespace std;

//
// 時間を計ったり、Updateを安定させるクラス
//
class Time final {


	static bool isInitialized;					//初期化できたか
	
	static long frameCount;						//現在までのフレーム経過数
	static float deltaTime;						//フレーム間時間
	static float time;							//現在までの経過時間
	
	static float fps;							//Frame per Seconds
	static float minFrameTime;					//目標となる処理時間

	static LARGE_INTEGER clockCountAwake;		//起動時のクロックカウント数
	static LARGE_INTEGER clockCountPrev;		//1フレーム前のクロックカウント数
	static LARGE_INTEGER clockCount;			//1フレームのクロックカウント数
	static LARGE_INTEGER clockCountFrequency;	//クロック数の精度


public:

	static bool Init(float fps);

	// 初期化してからの経過フレームを取得する
	static long GetFrameCount() {
		return frameCount;
	}

	// フレーム間時間を取得する
	static float GetDeltaTime() {
		return deltaTime;
	}

	// 初期化してからの経過時間を取得する
	static float GetTime() {
		return time;
	}

	// FPSを取得する
	static float GetFPS() {
		return fps;
	}

	// FPSの設定
	// vsyncの妨害を受ける
	static void SetFPS(float fps) {
		minFrameTime = 1.0f / fps;
	}

	// 時間を更新し、一定FPSを守るためにsleepする
	static void Update();

private:

	// 時間のみを更新する
	static void TimeUpdate();
};

