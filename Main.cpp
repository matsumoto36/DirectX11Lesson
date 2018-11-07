
//必要なヘッダーをインクルード
#include <Windows.h>				//Windowsプログラムで通常必要となるヘッダファイル

#include "Render.h"
#include "Shader.h"
#include "Mesh.h"
#include "Time.h"
#include "ControlObject.h"

//std. をタイプするのを省略する
using namespace std;
using namespace DirectX;



//
// Win32 アプリケーションの初期エントリポイント
// 
// パラメータ
// HINSTANCE  現在のインスタンスのハンドル
// HINSTANCE  以前のインスタンスのハンドル
// LPSTR      コマンドライン
// int        表示状態
//
// 戻り値
// 終了コード
//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//ウィンドウの初期化
	if (FAILED(Render::Init(hInstance, nCmdShow, "DirectX Lesson"))) {
		return 0;
	}

	//タイマーを60fpsで初期化
	Time::Init(60);

	auto obj = new ControlObject();
	obj->Start();

	//メッセージの構造体
	MSG hMsg = {};

	//構造体の初期化
	ZeroMemory(&hMsg, sizeof(hMsg));

	//基本ループ
	while (hMsg.message != WM_QUIT) {

		    //メッセージを重複しないように送信して結果を受け取る
		if (PeekMessage(&hMsg, nullptr, 0, 0, PM_REMOVE)) {
			//メッセージを受け取った場合
			
			TranslateMessage(&hMsg);	//メッセージを文字メッセージへ変換
			DispatchMessage(&hMsg);		//ウィンドウプロシージャへメッセージを送信
		}
		else {
			//メッセージを受け取らなかった場合//

			//描画をコントロールするオブジェクトのアップデート
			obj->Update();
			//操作されたポリゴンを描画
			Render::Rendering();
			//FPSの維持
			Time::Update();
		}
	}

	if (obj) delete obj;

	//デバイスとスワップチェインの開放
	Render::CleanupDevice();

	return 0;
}