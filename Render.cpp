#include "Render.h"

//描画するモデルのリスト
vector<reference_wrapper<Renderer>> Render::rendererList;

Camera* Render::_camera = nullptr;

int Render::windowSizeX = 1280;
int Render::windowSizeY = 720;

HWND Render::g_hWnd;

D3D_FEATURE_LEVEL		Render::g_pFeatureLevels[]
	= { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_1, D3D_FEATURE_LEVEL_10_0 };
UINT					Render::g_FeatureLevels = 3;
D3D_FEATURE_LEVEL		Render::g_FeatureLevelsSupported;

ID3D11Device*			Render::g_pd3dDevice = nullptr;
ID3D11DeviceContext*	Render::g_pImmedicateContext = nullptr;
IDXGISwapChain*			Render::g_pSwapChain = nullptr;
ID3D11RenderTargetView*	Render::g_pRenderTargetView = nullptr;
D3D11_VIEWPORT			Render::g_ViewPort;
ID3D11Texture2D*		Render::g_pDepthStencil = nullptr;
ID3D11DepthStencilView*	Render::g_pDepthStencilView = nullptr;

ID3D11BlendState*		Render::g_pBlendState = nullptr;
ID3D11RasterizerState*	Render::g_pRasterizerState = nullptr;

ID3D11SamplerState*		Render::g_pSamplerState = nullptr;

//
// ウィンドウプロシージャ
// ウィンドウから送られてくるメッセージを解釈して処理する
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		//閉じるボタンが押されたメッセージ
		case WM_CLOSE:
			//ウィンドウを削除するメッセージを書き込む（無視してもよい？）
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
			//ウィンドウ終了時のメッセージ
		case WM_DESTROY:
			//アプリケーションの終了コードを指定
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
			break;
		default:
			break;
	}

	//その他既定の処理を行う
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HRESULT Render::Init(HINSTANCE hInstance, int nCmdShow, const string& windowName) {

	InitWindow(hInstance, windowName);
	//ウィンドウの表示方法を指定して表示
	ShowWindow(g_hWnd, nCmdShow);
	//ウィンドウのクライアント領域を更新
	UpdateWindow(g_hWnd);

	return InitDevice();
}

//
// ウィンドウの初期化
//
void Render::InitWindow(HINSTANCE hInstance, const string& windowName) {

	TCHAR szWindowClass[] = "DIRECTX11 TUTORIAL003";	//ウィンドウクラスを識別する文字列を定義
	WNDCLASSEX weex;									//ウインドウクラスの構造体(EXではウィンドウのバーにアイコンがつけられる)
	weex.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEX構造体のサイズ
	weex.style = CS_HREDRAW | CS_VREDRAW;				//ウインドウスタイル(縦横のサイズが変わったときに再描画する)
	weex.lpfnWndProc = WndProc;							//ウインドウのメッセージを処理するコールバック関数へのポインタ
	weex.cbClsExtra = 0;								//ウインドウクラス構造体の後ろに割り当てる補足バイト数(通常0)
	weex.cbWndExtra = 0;								//ウインドウインスタンスの後ろに割り当てる補足バイト数(通常0)
	weex.hInstance = hInstance;							//ウインドウプロシージャがあるインスタンスハンドル
	weex.hIcon = nullptr;								//アイコンのハンドル
	weex.hCursor = nullptr;								//マウスカーソルのハンドル
	weex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//ウインドウ背景色(背景描画用ブラシのハンドル)
	weex.lpszMenuName = nullptr;						//デフォルトメニュー名
	weex.lpszClassName = szWindowClass;					//ウィンドウクラスを識別する文字列
	weex.hIconSm = nullptr;								//16×16の小さいサイズのアイコン

	//ウィンドウクラスを登録
	RegisterClassEx(&weex);

	//ウィンドウを生成
	g_hWnd = CreateWindow(
		szWindowClass,														//登録したクラスの名前
		windowName.c_str(),													//ウィンドウ枠に表示する文字列
		WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//ウインドウスタイル
		CW_USEDEFAULT,														//ウインドウ左上x座標(画面左上が0)
		CW_USEDEFAULT,														//ウインドウ左上y座標(画面左上が0)
		windowSizeX,														//ウインドウ幅
		windowSizeY,														//ウインドウ高さ
		nullptr,															//親ウインドウのハンドル
		nullptr,															//メニューのハンドル
		weex.hInstance,														//ウインドウとかを作成するモジュールのインスタンスのハンドル
		nullptr																//WM_CREATEでLPARAMに渡したい値
	);

}

HRESULT Render::InitDevice() {

	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC desc;						//SwapChainの情報指定
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;							//オフスクリーンの数

	//描画先の縦横サイズ、フォーマット(形式)を設定
	desc.BufferDesc.Width = windowSizeX;
	desc.BufferDesc.Height = windowSizeY;
	desc.BufferDesc.Format							//描画先の形式
		= DXGI_FORMAT_R8G8B8A8_UNORM;

	//描画先の更新頻度を分数形式で設定(Denominatorが分母)
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;

	desc.BufferDesc.ScanlineOrdering				//バックバッファをフリップした時にハードウェアがパソコンのモニターに点をどう描くかを指定
		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling							//バックバッファの絵を描画する時にウィンドウの大きさにスケーリングするかどうかを指定
		= DXGI_MODE_SCALING_UNSPECIFIED;

	//描画先の使用方法、描画先ウィンドウのハンドル、
	// ウィンドウモードか否か、MSAAのクオリティやカウント等を設定
	desc.BufferUsage								//バックバッファの使用制限についてのフラグをDXGI_USAGE列挙型で指定
		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = g_hWnd;						//ウィンドウハンドル
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;					//マルチサンプリングのクオリティ
	desc.Windowed = TRUE;							//ウィンドウモードかどうか
	desc.Flags										//フルスクリーン、ウィンドウを切り替えた際に自動変更されるようになる
		= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//他、desc.Flagsでは自動回転のオフやGDIの使用を可能にするなどの指定がある

	//スワップチェインの作成
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,					//どのビデオアダプタを使用するか？既定ならばnullptrで、IDXGIAdapterのアドレスを渡す
		D3D_DRIVER_TYPE_HARDWARE,	//ドライバのタイプを渡す。これ以外は基本的にソフトウェア実装で、どうしてもという時やデバグ用に用いるべし
		nullptr,					//上記をD3D_DRIVER_TYPE_SOFTWAREに設定した際に、その処理を行うDLLのハンドルを渡す。それ以外を指定している際には必ずnullptrを渡す
		0,							//何らかのフラグを指定する。詳しくはD3D11_CREATE_DEVICE列挙型で検索
		g_pFeatureLevels,			//ここでD3D_FEATURE_LEVEL列挙型の配列を与える。nullptrにすることで上記featureと同等の内容の配列が使用される
		1,							//上記引数で、自分で定義した配列を与えていた場合、その配列の要素数をここに記述する
		D3D11_SDK_VERSION,			//SDKのバージョン。必ずこの値.
		&desc,						//DXGI_SWAP_CHAIN_DESC構造体のアドレスを設定する。ここで設定した構造体に設定されているパラメータでSwapChainが作成される
		&g_pSwapChain,				//作成が成功した場合に、そのSwapChainのアドレスを格納するポインタ変数へのアドレス。ここで指定したポインタ変数経由でSwapChainを操作する
		&g_pd3dDevice,				//上記とほぼ同様で、こちらにはDeviceのポインタ変数のアドレスを設定する
		&g_FeatureLevelsSupported,	//実際に作成に成功したD3D_FEATURE_LEVELを格納するためのD3D_FEATURE_LEVEL列挙型変数のアドレスを設定する
		&g_pImmedicateContext);		//SwapChainやDeviceと同様に、こちらにはContextのポインタ変数のアドレスを設定する

	if (FAILED(hr)) return E_FAIL;

	//バックバッファの作成
	ID3D11Texture2D* pBackBuffer;
	hr = g_pSwapChain->GetBuffer(
		0,							//バッファーインデックス
		__uuidof(ID3D11Texture2D),	//バックバッファのインターフェイスのGUID
		(LPVOID*)&pBackBuffer		//関数が成功したときに返るバックバッファへのポインタ
	);

	if (FAILED(hr)) return E_FAIL;

	//描画ターゲットビューの生成
	hr = g_pd3dDevice->CreateRenderTargetView(
		pBackBuffer,			//ビューに関連付けるリソースであるID3D10Resouceインターフェイスへのポインタ
		nullptr,				//描画ターゲットビューの能力をD3D10_RENDER_TARGET_VIEW_DESC構造体で指定
		&g_pRenderTargetView	//関数が成功したときに返る描画ターゲットビューインターフェイスへのポインタ
	);

	if (FAILED(hr)) return E_FAIL;

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = windowSizeX;					//テクスチャの幅
	descDepth.Height = windowSizeY;					//テクスチャの高さ
	descDepth.MipLevels = 1;						//テクスチャ内のミップマップ レベルの最大数
	descDepth.ArraySize = 1;						//テクスチャ配列内のテクスチャーの数
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;		//テキスチャフォーマット
	descDepth.SampleDesc.Count = 1;					//ピクセル単位のマルチサンプリングの数
	descDepth.SampleDesc.Quality = 0;				//マルチサンプリング品質レベル
	descDepth.Usage = D3D11_USAGE_DEFAULT;			//テクスチャの読み込みおよび書き込み方法を識別する値
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//パイプラインステージへのバインドに関するフラグ
	descDepth.CPUAccessFlags = 0;					//許可するCPUアクセスの種類を指定するフラグ
	descDepth.MiscFlags = 0;						//他の一般性の低いリソースオプションを識別するフラグ

													//2Dテクスチャーの配列を作成
	hr = g_pd3dDevice->CreateTexture2D(
		&descDepth,			//2Dテクスチャの記述へのポインタ
		nullptr,			//サブリソースの記述の配列へのポインタ
		&g_pDepthStencil	//作成されるテクスチャへのポインターのアドレス
	);

	//深度ステンシルビューからアクセス可能なテクスチャのサブリソース
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;		//リソースデータのフォーマット
	descDSV.ViewDimension					//深度ステンシルリソースへのアクセス方法を指定
		= D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Flags = 0;						//テクスチャが読み取り専用かどうか(読み取り専用でないなら0)
	descDSV.Texture2D.MipSlice = 0;			//最初に使用するミップマップレベルのインデックス

											//リソースデータへのアクセス用に深度ステンシルビューを作成
	hr = g_pd3dDevice->CreateDepthStencilView(
		g_pDepthStencil,		//深度ステンシルサーフェスとして機能するリソースへのポインタ
		&descDSV,				//深度ステンシルビューの記述へのポインタ
		&g_pDepthStencilView	//ID3D11DepthStencilViewへのポインターのアドレス
	);

	if (FAILED(hr)) return E_FAIL;

	//レンダーターゲットをアトミックにバインドし、出力結合ステージに深度ステンシルバッファーをバインド
	g_pImmedicateContext->OMSetRenderTargets(
		1,						//バインドするレンダー ターゲットの数
		&g_pRenderTargetView,	//デバイスにバインドするレンダー ターゲットの配列へのポインタ
		g_pDepthStencilView		//デバイスにバインドする深度ステンシル ビューへのポインタ
	);

	g_ViewPort.TopLeftX = 0.0f;							//ビューポートの左側のX位置
	g_ViewPort.TopLeftY = 0.0f;							//ビューポートの上部のY位置
	g_ViewPort.Width = static_cast<float>(windowSizeX);	//ビューポートの幅
	g_ViewPort.Height = static_cast<float>(windowSizeY);	//ビューポートの高さ
	g_ViewPort.MinDepth = 0.0f;							//ビューポートの最小深度
	g_ViewPort.MaxDepth = 1.0f;							//ビューポートの最大深度

	//パイプラインのラスタライザーステージにビューポートの配列をバインド
	g_pImmedicateContext->RSSetViewports(1, &g_ViewPort);

	//ポリゴンの裏面を表示する処理---
	//初期化
	D3D11_RASTERIZER_DESC descRast = {
		D3D11_FILL_SOLID,	//レンダリング時に使用する描画モードを設定
		D3D11_CULL_NONE,	//カリングの設定
		FALSE,				//三角形が前向きか後ろ向きかを設定する
		0,					//指定のピクセルに加算する深度値
		0.0f,				//ピクセルの最大深度バイアス
		0.0f,				//ピクセルの傾斜に基づいてバイアスをかける
		FALSE,				//距離に応じてクリッピングを有効にする
		FALSE,				//シザー矩形カリングを有効にする
		FALSE,				//マルチサンプリングのアンチエイリアシングを有効にする
		FALSE				//線のアンチエイリアシングを有効にする
	};

	//ラスタライザステージに動作を支持するラスタライザステートオブジェクトを作成
	g_pd3dDevice->CreateRasterizerState(
		&descRast,				//ラスタライザステートの記述へのポインタ
		&g_pRasterizerState		//作成されるラスタライザステートオブジェクトへのポインタのアドレス
	);

	//パイプラインのラスタライザステージのラスタライザステートを設定
	g_pImmedicateContext->RSSetState(g_pRasterizerState);

	if (FAILED(hr)) return E_FAIL;

	//ブレンディングステートの設定
	D3D11_BLEND_DESC descBlend;
	ZeroMemory(&descBlend, sizeof(descBlend));
	descBlend.AlphaToCoverageEnable = FALSE;											//アルファテストを適用させた場所にも、アンチエリアス処理を行えるか
	descBlend.IndependentBlendEnable = FALSE;											//同時処理のレンダーターゲットで独立したブレンディングを有効にするか
	descBlend.RenderTarget[0].BlendEnable = TRUE;										//ブレンディングを有効にするか
	descBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;							//最初のRGBデータソースを指定
	descBlend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;					//2番目のRGBデータソースを指定
	descBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;								//RGBデータソースの組合せ方法を定義
	descBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;							//最初のアルファデータソースを指定
	descBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;						//2番目のアルファデータソースを指定
	descBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;						//アルファデータソースの組合せ方法を定義
	descBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//書き込みマスク

	//出力結合ステージ用にブレンディングステートをカプセル化するブレンドステートオブジェクトを作成
	g_pd3dDevice->CreateBlendState(
		&descBlend,		//ブレンディングステートへのポインタ
		&g_pBlendState	//作成されるブレンディングステートオブジェクトへのポインタ
	);

	//ブレンディング係数の配列を定義(RGBAひとつづつ)
	float blendFactor[4] = {
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO
	};

	//出力結合ステージのブレンディングステートを設定
	g_pImmedicateContext->OMSetBlendState(
		g_pBlendState,	//ブレンディングステートインターフェイスへのポインタ
		blendFactor,	//ブレンディング係数の配列
		0xffffffff		//32ビットのサンプルカバレッジ。既定値は 0xffffffff
	);

	//シェーダーの初期設定
	if (FAILED(Shader::Initialize(*g_pd3dDevice))) return E_FAIL;

	//必要な情報をセット
	Renderer::SetRenderData(
		g_pd3dDevice,
		rendererList
	);

	if (FAILED(hr)) return E_FAIL;

	//カメラの生成
	_camera = new Camera({ 0, 0, -2 }, g_ViewPort.Width / g_ViewPort.Height);

	//サンプラーステートの作成
	D3D11_SAMPLER_DESC descSampler;

	ZeroMemory(&descSampler, sizeof(D3D11_SAMPLER_DESC));
	descSampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSampler.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	descSampler.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	descSampler.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = g_pd3dDevice->CreateSamplerState(
		&descSampler,
		&g_pSamplerState);

	//サンプラーステートを転送
	g_pImmedicateContext->PSSetSamplers(
		0,
		1,
		&g_pSamplerState
	);

	//初期設定
	Texture::SetInitData(g_pd3dDevice);

	return hr;
}

void Render::RenderClear() {

	float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	//背景の色を設定 レンダーターゲットクリア
	g_pImmedicateContext->ClearRenderTargetView(g_pRenderTargetView, Colors::Black);
	//深度・ステンシルバッファクリア
	g_pImmedicateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void Render::Rendering() {

	RenderClear();

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	for (size_t i = 0; i < rendererList.size(); i++) {

		auto renderer = &rendererList[i].get();

		if (!renderer->IsRender) continue;


		//サブリソースの更新
		renderer->OnUpdateSubResource(g_pImmedicateContext);

		//行列を転置
		auto world = XMMatrixTranspose(renderer->GetTransform());	//ワールド変換行列
		auto view = XMMatrixTranspose(_camera->GetView());						//ビュー変換行列
		auto projection = XMMatrixTranspose(_camera->GetProj());				//プロジェクション変換行列

		if (auto material = renderer->GetMaterial()) {

			//行列データを転送
			material->SetMatrix("World", world);
			material->SetMatrix("View", view);
			material->SetMatrix("Projection", projection);

			//シェーダーを設定
			material->SetShader(*g_pImmedicateContext);

			//コンスタントバッファの更新
			material->UpdateConstantBuffer(*g_pImmedicateContext);
			material->SetConstantBuffer(*g_pImmedicateContext);
		}

		//テクスチャ系
		if (auto material = renderer->GetMaterial()) {
			material->UpdateShaderResourceView(*g_pImmedicateContext);
			material->UpdateSampler(*g_pImmedicateContext);

			//入力アセンブラーステージに入力レイアウトオブジェクトをバインド
			material->SetInputLayout(*g_pImmedicateContext);
		}

		//入力アセンブラーステージに頂点バッファーの配列をバインド
		g_pImmedicateContext->IASetVertexBuffers(
			0,								//バインドに使用する最初の入力スロット
			1,								//配列内の頂点バッファーの数
			&renderer->GetVertexBuffer(),	//頂点バッファーの配列へのポインター
			&strides,						//ストライド値 : 頂点バッファーで使用される要素のサイズ (バイト単位)
			&offsets						//オフセット値 : 頂点バッファー内の先頭の要素と、使用される最初の要素との間隔
		);

		//インデックスバッファを設定
		if(auto indexBuffer = renderer->GetIndexBuffer())
			g_pImmedicateContext->IASetIndexBuffer(
				indexBuffer,
				DXGI_FORMAT_R32_UINT,
				0
			);

		//プリミティブ タイプおよびデータの順序に関する情報をバインド 
		renderer->SetPrimitiveTopology(g_pImmedicateContext);

		//描画
		renderer->OnDraw(g_pImmedicateContext);

	}

	//レンダリングされたイメージを画面に描画する
	g_pSwapChain->Present(0, 0);
}

//
// 各種リソースを破棄する。
//
void Render::CleanupDevice() {

	//デバイスコンテキストを既定の設定にリセット
	if (g_pImmedicateContext) g_pImmedicateContext->ClearState();

	//リソースの開放
	Shader::Finalize();

	if (_camera) delete _camera;

	if (g_pDepthStencilView) g_pDepthStencilView->Release();
	if (g_pDepthStencil) g_pDepthStencil->Release();
	if (g_pRenderTargetView) g_pRenderTargetView->Release();
	if (g_pSwapChain) g_pSwapChain->Release();
	if (g_pImmedicateContext) g_pImmedicateContext->Release();
	if (g_pd3dDevice) g_pd3dDevice->Release();

	if (g_pBlendState) g_pBlendState->Release();
	if (g_pRasterizerState) g_pRasterizerState->Release();
}