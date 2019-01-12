#pragma once

//必要なヘッダーをインクルード
#include <tchar.h>					//Microsoft固有の汎用テキストのマッピング
#include <Windows.h>				//Windowsプログラムで通常必要となるヘッダファイル
#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>

#include "Camera.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "ControlObject.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

//std. をタイプするのを省略する
using namespace std;
using namespace DirectX;

//
// レンダラに従って描画を行うクラス
//
class Render final {

	//描画するレンダラのリスト
	static vector<reference_wrapper<Renderer>> rendererList;

	static Camera*					_camera;

	//ウィンドウサイズ
	static int windowSizeX;
	static int windowSizeY;

	//ウィンドウオブジェクト
	static HWND g_hWnd;

	static D3D_FEATURE_LEVEL		g_pFeatureLevels[];			//デバイスの機能レベルのリストを定義
		
	static UINT						g_FeatureLevels;			//ターゲットの要素数
	static D3D_FEATURE_LEVEL		g_FeatureLevelsSupported;	//デバイス作成時に返されるバージョン

	static ID3D11Device*			g_pd3dDevice;				//レンダリング及びリソースの作成に使用
	static ID3D11DeviceContext*		g_pImmedicateContext;		//レンダリングコマンドを生成するデバイスコマンド
	static IDXGISwapChain*			g_pSwapChain;				//レンダリングデータを表示前に格納する
	static ID3D11RenderTargetView*	g_pRenderTargetView;		//レンダリング時にレンダーターゲットのサブリソースを識別
	static D3D11_VIEWPORT			g_ViewPort;					//ビューポートの寸法を定義
	static ID3D11Texture2D*			g_pDepthStencil;			//深度・ステンシルリソースとして使用
	static ID3D11DepthStencilView*	g_pDepthStencilView;		//深度・ステンシルリソースにアクセスする

	static ID3D11BlendState*		g_pBlendState;				//アルファブレンド
	static ID3D11RasterizerState*	g_pRasterizerState;			//ラスタライザー

	static ID3D11SamplerState*		g_pSamplerState;			//テクスチャのサンプラーステート

public:

private:
	Render();

public:
	
	static HRESULT Init(HINSTANCE hInstance, int nCmdShow, const string& windowName);
	static void CleanupDevice();					//デバイスとスワップチェインの開放
	static Camera& GetCamera() { return *_camera; }
	static void Rendering();						//描画を行う

private:

	static void InitWindow(HINSTANCE hInstance, const string& windowName);
	static HRESULT InitDevice();					//デバイスとスワップチェインの初期化
	static void RenderClear();						//描画を消す

};