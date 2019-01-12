#include "Render.h"

//�`�悷�郂�f���̃��X�g
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
// �E�B���h�E�v���V�[�W��
// �E�B���h�E���瑗���Ă��郁�b�Z�[�W�����߂��ď�������
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {

		//����{�^���������ꂽ���b�Z�[�W
		case WM_CLOSE:
			//�E�B���h�E���폜���郁�b�Z�[�W���������ށi�������Ă��悢�H�j
			PostMessage(hWnd, WM_DESTROY, 0, 0);
			break;
			//�E�B���h�E�I�����̃��b�Z�[�W
		case WM_DESTROY:
			//�A�v���P�[�V�����̏I���R�[�h���w��
			PostQuitMessage(0);
			break;
		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE)
				DestroyWindow(hWnd);
			break;
		default:
			break;
	}

	//���̑�����̏������s��
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HRESULT Render::Init(HINSTANCE hInstance, int nCmdShow, const string& windowName) {

	InitWindow(hInstance, windowName);
	//�E�B���h�E�̕\�����@���w�肵�ĕ\��
	ShowWindow(g_hWnd, nCmdShow);
	//�E�B���h�E�̃N���C�A���g�̈���X�V
	UpdateWindow(g_hWnd);

	return InitDevice();
}

//
// �E�B���h�E�̏�����
//
void Render::InitWindow(HINSTANCE hInstance, const string& windowName) {

	TCHAR szWindowClass[] = "DIRECTX11 TUTORIAL003";	//�E�B���h�E�N���X�����ʂ��镶������`
	WNDCLASSEX weex;									//�E�C���h�E�N���X�̍\����(EX�ł̓E�B���h�E�̃o�[�ɃA�C�R����������)
	weex.cbSize = sizeof(WNDCLASSEX);					//WNDCLASSEX�\���̂̃T�C�Y
	weex.style = CS_HREDRAW | CS_VREDRAW;				//�E�C���h�E�X�^�C��(�c���̃T�C�Y���ς�����Ƃ��ɍĕ`�悷��)
	weex.lpfnWndProc = WndProc;							//�E�C���h�E�̃��b�Z�[�W����������R�[���o�b�N�֐��ւ̃|�C���^
	weex.cbClsExtra = 0;								//�E�C���h�E�N���X�\���̂̌��Ɋ��蓖�Ă�⑫�o�C�g��(�ʏ�0)
	weex.cbWndExtra = 0;								//�E�C���h�E�C���X�^���X�̌��Ɋ��蓖�Ă�⑫�o�C�g��(�ʏ�0)
	weex.hInstance = hInstance;							//�E�C���h�E�v���V�[�W��������C���X�^���X�n���h��
	weex.hIcon = nullptr;								//�A�C�R���̃n���h��
	weex.hCursor = nullptr;								//�}�E�X�J�[�\���̃n���h��
	weex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);	//�E�C���h�E�w�i�F(�w�i�`��p�u���V�̃n���h��)
	weex.lpszMenuName = nullptr;						//�f�t�H���g���j���[��
	weex.lpszClassName = szWindowClass;					//�E�B���h�E�N���X�����ʂ��镶����
	weex.hIconSm = nullptr;								//16�~16�̏������T�C�Y�̃A�C�R��

	//�E�B���h�E�N���X��o�^
	RegisterClassEx(&weex);

	//�E�B���h�E�𐶐�
	g_hWnd = CreateWindow(
		szWindowClass,														//�o�^�����N���X�̖��O
		windowName.c_str(),													//�E�B���h�E�g�ɕ\�����镶����
		WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//�E�C���h�E�X�^�C��
		CW_USEDEFAULT,														//�E�C���h�E����x���W(��ʍ��オ0)
		CW_USEDEFAULT,														//�E�C���h�E����y���W(��ʍ��オ0)
		windowSizeX,														//�E�C���h�E��
		windowSizeY,														//�E�C���h�E����
		nullptr,															//�e�E�C���h�E�̃n���h��
		nullptr,															//���j���[�̃n���h��
		weex.hInstance,														//�E�C���h�E�Ƃ����쐬���郂�W���[���̃C���X�^���X�̃n���h��
		nullptr																//WM_CREATE��LPARAM�ɓn�������l
	);

}

HRESULT Render::InitDevice() {

	HRESULT hr = S_OK;

	DXGI_SWAP_CHAIN_DESC desc;						//SwapChain�̏��w��
	ZeroMemory(&desc, sizeof(desc));
	desc.BufferCount = 1;							//�I�t�X�N���[���̐�

	//�`���̏c���T�C�Y�A�t�H�[�}�b�g(�`��)��ݒ�
	desc.BufferDesc.Width = windowSizeX;
	desc.BufferDesc.Height = windowSizeY;
	desc.BufferDesc.Format							//�`���̌`��
		= DXGI_FORMAT_R8G8B8A8_UNORM;

	//�`���̍X�V�p�x�𕪐��`���Őݒ�(Denominator������)
	desc.BufferDesc.RefreshRate.Numerator = 60;
	desc.BufferDesc.RefreshRate.Denominator = 1;

	desc.BufferDesc.ScanlineOrdering				//�o�b�N�o�b�t�@���t���b�v�������Ƀn�[�h�E�F�A���p�\�R���̃��j�^�[�ɓ_���ǂ��`�������w��
		= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	desc.BufferDesc.Scaling							//�o�b�N�o�b�t�@�̊G��`�悷�鎞�ɃE�B���h�E�̑傫���ɃX�P�[�����O���邩�ǂ������w��
		= DXGI_MODE_SCALING_UNSPECIFIED;

	//�`���̎g�p���@�A�`���E�B���h�E�̃n���h���A
	// �E�B���h�E���[�h���ۂ��AMSAA�̃N�I���e�B��J�E���g����ݒ�
	desc.BufferUsage								//�o�b�N�o�b�t�@�̎g�p�����ɂ��Ẵt���O��DXGI_USAGE�񋓌^�Ŏw��
		= DXGI_USAGE_RENDER_TARGET_OUTPUT;
	desc.OutputWindow = g_hWnd;						//�E�B���h�E�n���h��
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;					//�}���`�T���v�����O�̃N�I���e�B
	desc.Windowed = TRUE;							//�E�B���h�E���[�h���ǂ���
	desc.Flags										//�t���X�N���[���A�E�B���h�E��؂�ւ����ۂɎ����ύX�����悤�ɂȂ�
		= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;	//���Adesc.Flags�ł͎�����]�̃I�t��GDI�̎g�p���\�ɂ���Ȃǂ̎w�肪����

	//�X���b�v�`�F�C���̍쐬
	hr = D3D11CreateDeviceAndSwapChain(
		nullptr,					//�ǂ̃r�f�I�A�_�v�^���g�p���邩�H����Ȃ��nullptr�ŁAIDXGIAdapter�̃A�h���X��n��
		D3D_DRIVER_TYPE_HARDWARE,	//�h���C�o�̃^�C�v��n���B����ȊO�͊�{�I�Ƀ\�t�g�E�F�A�����ŁA�ǂ����Ă��Ƃ�������f�o�O�p�ɗp����ׂ�
		nullptr,					//��L��D3D_DRIVER_TYPE_SOFTWARE�ɐݒ肵���ۂɁA���̏������s��DLL�̃n���h����n���B����ȊO���w�肵�Ă���ۂɂ͕K��nullptr��n��
		0,							//���炩�̃t���O���w�肷��B�ڂ�����D3D11_CREATE_DEVICE�񋓌^�Ō���
		g_pFeatureLevels,			//������D3D_FEATURE_LEVEL�񋓌^�̔z���^����Bnullptr�ɂ��邱�Ƃŏ�Lfeature�Ɠ����̓��e�̔z�񂪎g�p�����
		1,							//��L�����ŁA�����Œ�`�����z���^���Ă����ꍇ�A���̔z��̗v�f���������ɋL�q����
		D3D11_SDK_VERSION,			//SDK�̃o�[�W�����B�K�����̒l.
		&desc,						//DXGI_SWAP_CHAIN_DESC�\���̂̃A�h���X��ݒ肷��B�����Őݒ肵���\���̂ɐݒ肳��Ă���p�����[�^��SwapChain���쐬�����
		&g_pSwapChain,				//�쐬�����������ꍇ�ɁA����SwapChain�̃A�h���X���i�[����|�C���^�ϐ��ւ̃A�h���X�B�����Ŏw�肵���|�C���^�ϐ��o�R��SwapChain�𑀍삷��
		&g_pd3dDevice,				//��L�Ƃقړ��l�ŁA������ɂ�Device�̃|�C���^�ϐ��̃A�h���X��ݒ肷��
		&g_FeatureLevelsSupported,	//���ۂɍ쐬�ɐ�������D3D_FEATURE_LEVEL���i�[���邽�߂�D3D_FEATURE_LEVEL�񋓌^�ϐ��̃A�h���X��ݒ肷��
		&g_pImmedicateContext);		//SwapChain��Device�Ɠ��l�ɁA������ɂ�Context�̃|�C���^�ϐ��̃A�h���X��ݒ肷��

	if (FAILED(hr)) return E_FAIL;

	//�o�b�N�o�b�t�@�̍쐬
	ID3D11Texture2D* pBackBuffer;
	hr = g_pSwapChain->GetBuffer(
		0,							//�o�b�t�@�[�C���f�b�N�X
		__uuidof(ID3D11Texture2D),	//�o�b�N�o�b�t�@�̃C���^�[�t�F�C�X��GUID
		(LPVOID*)&pBackBuffer		//�֐������������Ƃ��ɕԂ�o�b�N�o�b�t�@�ւ̃|�C���^
	);

	if (FAILED(hr)) return E_FAIL;

	//�`��^�[�Q�b�g�r���[�̐���
	hr = g_pd3dDevice->CreateRenderTargetView(
		pBackBuffer,			//�r���[�Ɋ֘A�t���郊�\�[�X�ł���ID3D10Resouce�C���^�[�t�F�C�X�ւ̃|�C���^
		nullptr,				//�`��^�[�Q�b�g�r���[�̔\�͂�D3D10_RENDER_TARGET_VIEW_DESC�\���̂Ŏw��
		&g_pRenderTargetView	//�֐������������Ƃ��ɕԂ�`��^�[�Q�b�g�r���[�C���^�[�t�F�C�X�ւ̃|�C���^
	);

	if (FAILED(hr)) return E_FAIL;

	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = windowSizeX;					//�e�N�X�`���̕�
	descDepth.Height = windowSizeY;					//�e�N�X�`���̍���
	descDepth.MipLevels = 1;						//�e�N�X�`�����̃~�b�v�}�b�v ���x���̍ő吔
	descDepth.ArraySize = 1;						//�e�N�X�`���z����̃e�N�X�`���[�̐�
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;		//�e�L�X�`���t�H�[�}�b�g
	descDepth.SampleDesc.Count = 1;					//�s�N�Z���P�ʂ̃}���`�T���v�����O�̐�
	descDepth.SampleDesc.Quality = 0;				//�}���`�T���v�����O�i�����x��
	descDepth.Usage = D3D11_USAGE_DEFAULT;			//�e�N�X�`���̓ǂݍ��݂���я������ݕ��@�����ʂ���l
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//�p�C�v���C���X�e�[�W�ւ̃o�C���h�Ɋւ���t���O
	descDepth.CPUAccessFlags = 0;					//������CPU�A�N�Z�X�̎�ނ��w�肷��t���O
	descDepth.MiscFlags = 0;						//���̈�ʐ��̒Ⴂ���\�[�X�I�v�V���������ʂ���t���O

													//2D�e�N�X�`���[�̔z����쐬
	hr = g_pd3dDevice->CreateTexture2D(
		&descDepth,			//2D�e�N�X�`���̋L�q�ւ̃|�C���^
		nullptr,			//�T�u���\�[�X�̋L�q�̔z��ւ̃|�C���^
		&g_pDepthStencil	//�쐬�����e�N�X�`���ւ̃|�C���^�[�̃A�h���X
	);

	//�[�x�X�e���V���r���[����A�N�Z�X�\�ȃe�N�X�`���̃T�u���\�[�X
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
	descDSV.Format = descDepth.Format;		//���\�[�X�f�[�^�̃t�H�[�}�b�g
	descDSV.ViewDimension					//�[�x�X�e���V�����\�[�X�ւ̃A�N�Z�X���@���w��
		= D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Flags = 0;						//�e�N�X�`�����ǂݎ���p���ǂ���(�ǂݎ���p�łȂ��Ȃ�0)
	descDSV.Texture2D.MipSlice = 0;			//�ŏ��Ɏg�p����~�b�v�}�b�v���x���̃C���f�b�N�X

											//���\�[�X�f�[�^�ւ̃A�N�Z�X�p�ɐ[�x�X�e���V���r���[���쐬
	hr = g_pd3dDevice->CreateDepthStencilView(
		g_pDepthStencil,		//�[�x�X�e���V���T�[�t�F�X�Ƃ��ċ@�\���郊�\�[�X�ւ̃|�C���^
		&descDSV,				//�[�x�X�e���V���r���[�̋L�q�ւ̃|�C���^
		&g_pDepthStencilView	//ID3D11DepthStencilView�ւ̃|�C���^�[�̃A�h���X
	);

	if (FAILED(hr)) return E_FAIL;

	//�����_�[�^�[�Q�b�g���A�g�~�b�N�Ƀo�C���h���A�o�͌����X�e�[�W�ɐ[�x�X�e���V���o�b�t�@�[���o�C���h
	g_pImmedicateContext->OMSetRenderTargets(
		1,						//�o�C���h���郌���_�[ �^�[�Q�b�g�̐�
		&g_pRenderTargetView,	//�f�o�C�X�Ƀo�C���h���郌���_�[ �^�[�Q�b�g�̔z��ւ̃|�C���^
		g_pDepthStencilView		//�f�o�C�X�Ƀo�C���h����[�x�X�e���V�� �r���[�ւ̃|�C���^
	);

	g_ViewPort.TopLeftX = 0.0f;							//�r���[�|�[�g�̍�����X�ʒu
	g_ViewPort.TopLeftY = 0.0f;							//�r���[�|�[�g�̏㕔��Y�ʒu
	g_ViewPort.Width = static_cast<float>(windowSizeX);	//�r���[�|�[�g�̕�
	g_ViewPort.Height = static_cast<float>(windowSizeY);	//�r���[�|�[�g�̍���
	g_ViewPort.MinDepth = 0.0f;							//�r���[�|�[�g�̍ŏ��[�x
	g_ViewPort.MaxDepth = 1.0f;							//�r���[�|�[�g�̍ő�[�x

	//�p�C�v���C���̃��X�^���C�U�[�X�e�[�W�Ƀr���[�|�[�g�̔z����o�C���h
	g_pImmedicateContext->RSSetViewports(1, &g_ViewPort);

	//�|���S���̗��ʂ�\�����鏈��---
	//������
	D3D11_RASTERIZER_DESC descRast = {
		D3D11_FILL_SOLID,	//�����_�����O���Ɏg�p����`�惂�[�h��ݒ�
		D3D11_CULL_NONE,	//�J�����O�̐ݒ�
		FALSE,				//�O�p�`���O����������������ݒ肷��
		0,					//�w��̃s�N�Z���ɉ��Z����[�x�l
		0.0f,				//�s�N�Z���̍ő�[�x�o�C�A�X
		0.0f,				//�s�N�Z���̌X�΂Ɋ�Â��ăo�C�A�X��������
		FALSE,				//�����ɉ����ăN���b�s���O��L���ɂ���
		FALSE,				//�V�U�[��`�J�����O��L���ɂ���
		FALSE,				//�}���`�T���v�����O�̃A���`�G�C���A�V���O��L���ɂ���
		FALSE				//���̃A���`�G�C���A�V���O��L���ɂ���
	};

	//���X�^���C�U�X�e�[�W�ɓ�����x�����郉�X�^���C�U�X�e�[�g�I�u�W�F�N�g���쐬
	g_pd3dDevice->CreateRasterizerState(
		&descRast,				//���X�^���C�U�X�e�[�g�̋L�q�ւ̃|�C���^
		&g_pRasterizerState		//�쐬����郉�X�^���C�U�X�e�[�g�I�u�W�F�N�g�ւ̃|�C���^�̃A�h���X
	);

	//�p�C�v���C���̃��X�^���C�U�X�e�[�W�̃��X�^���C�U�X�e�[�g��ݒ�
	g_pImmedicateContext->RSSetState(g_pRasterizerState);

	if (FAILED(hr)) return E_FAIL;

	//�u�����f�B���O�X�e�[�g�̐ݒ�
	D3D11_BLEND_DESC descBlend;
	ZeroMemory(&descBlend, sizeof(descBlend));
	descBlend.AlphaToCoverageEnable = FALSE;											//�A���t�@�e�X�g��K�p�������ꏊ�ɂ��A�A���`�G���A�X�������s���邩
	descBlend.IndependentBlendEnable = FALSE;											//���������̃����_�[�^�[�Q�b�g�œƗ������u�����f�B���O��L���ɂ��邩
	descBlend.RenderTarget[0].BlendEnable = TRUE;										//�u�����f�B���O��L���ɂ��邩
	descBlend.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;							//�ŏ���RGB�f�[�^�\�[�X���w��
	descBlend.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;					//2�Ԗڂ�RGB�f�[�^�\�[�X���w��
	descBlend.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;								//RGB�f�[�^�\�[�X�̑g�������@���`
	descBlend.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;							//�ŏ��̃A���t�@�f�[�^�\�[�X���w��
	descBlend.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;						//2�Ԗڂ̃A���t�@�f�[�^�\�[�X���w��
	descBlend.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;						//�A���t�@�f�[�^�\�[�X�̑g�������@���`
	descBlend.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;		//�������݃}�X�N

	//�o�͌����X�e�[�W�p�Ƀu�����f�B���O�X�e�[�g���J�v�Z��������u�����h�X�e�[�g�I�u�W�F�N�g���쐬
	g_pd3dDevice->CreateBlendState(
		&descBlend,		//�u�����f�B���O�X�e�[�g�ւ̃|�C���^
		&g_pBlendState	//�쐬�����u�����f�B���O�X�e�[�g�I�u�W�F�N�g�ւ̃|�C���^
	);

	//�u�����f�B���O�W���̔z����`(RGBA�ЂƂÂ�)
	float blendFactor[4] = {
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO,
		D3D11_BLEND_ZERO
	};

	//�o�͌����X�e�[�W�̃u�����f�B���O�X�e�[�g��ݒ�
	g_pImmedicateContext->OMSetBlendState(
		g_pBlendState,	//�u�����f�B���O�X�e�[�g�C���^�[�t�F�C�X�ւ̃|�C���^
		blendFactor,	//�u�����f�B���O�W���̔z��
		0xffffffff		//32�r�b�g�̃T���v���J�o���b�W�B����l�� 0xffffffff
	);

	//�V�F�[�_�[�̏����ݒ�
	if (FAILED(Shader::Initialize(*g_pd3dDevice))) return E_FAIL;

	//�K�v�ȏ����Z�b�g
	Renderer::SetRenderData(
		g_pd3dDevice,
		rendererList
	);

	if (FAILED(hr)) return E_FAIL;

	//�J�����̐���
	_camera = new Camera({ 0, 0, -2 }, g_ViewPort.Width / g_ViewPort.Height);

	//�T���v���[�X�e�[�g�̍쐬
	D3D11_SAMPLER_DESC descSampler;

	ZeroMemory(&descSampler, sizeof(D3D11_SAMPLER_DESC));
	descSampler.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	descSampler.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	descSampler.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	descSampler.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = g_pd3dDevice->CreateSamplerState(
		&descSampler,
		&g_pSamplerState);

	//�T���v���[�X�e�[�g��]��
	g_pImmedicateContext->PSSetSamplers(
		0,
		1,
		&g_pSamplerState
	);

	//�����ݒ�
	Texture::SetInitData(g_pd3dDevice);

	return hr;
}

void Render::RenderClear() {

	float ClearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };

	//�w�i�̐F��ݒ� �����_�[�^�[�Q�b�g�N���A
	g_pImmedicateContext->ClearRenderTargetView(g_pRenderTargetView, Colors::Black);
	//�[�x�E�X�e���V���o�b�t�@�N���A
	g_pImmedicateContext->ClearDepthStencilView(g_pDepthStencilView, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

}

void Render::Rendering() {

	RenderClear();

	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	for (size_t i = 0; i < rendererList.size(); i++) {

		auto renderer = &rendererList[i].get();

		if (!renderer->IsRender) continue;


		//�T�u���\�[�X�̍X�V
		renderer->OnUpdateSubResource(g_pImmedicateContext);

		//�s���]�u
		auto world = XMMatrixTranspose(renderer->GetTransform());	//���[���h�ϊ��s��
		auto view = XMMatrixTranspose(_camera->GetView());						//�r���[�ϊ��s��
		auto projection = XMMatrixTranspose(_camera->GetProj());				//�v���W�F�N�V�����ϊ��s��

		if (auto material = renderer->GetMaterial()) {

			//�s��f�[�^��]��
			material->SetMatrix("World", world);
			material->SetMatrix("View", view);
			material->SetMatrix("Projection", projection);

			//�V�F�[�_�[��ݒ�
			material->SetShader(*g_pImmedicateContext);

			//�R���X�^���g�o�b�t�@�̍X�V
			material->UpdateConstantBuffer(*g_pImmedicateContext);
			material->SetConstantBuffer(*g_pImmedicateContext);
		}

		//�e�N�X�`���n
		if (auto material = renderer->GetMaterial()) {
			material->UpdateShaderResourceView(*g_pImmedicateContext);
			material->UpdateSampler(*g_pImmedicateContext);

			//���̓A�Z���u���[�X�e�[�W�ɓ��̓��C�A�E�g�I�u�W�F�N�g���o�C���h
			material->SetInputLayout(*g_pImmedicateContext);
		}

		//���̓A�Z���u���[�X�e�[�W�ɒ��_�o�b�t�@�[�̔z����o�C���h
		g_pImmedicateContext->IASetVertexBuffers(
			0,								//�o�C���h�Ɏg�p����ŏ��̓��̓X���b�g
			1,								//�z����̒��_�o�b�t�@�[�̐�
			&renderer->GetVertexBuffer(),	//���_�o�b�t�@�[�̔z��ւ̃|�C���^�[
			&strides,						//�X�g���C�h�l : ���_�o�b�t�@�[�Ŏg�p�����v�f�̃T�C�Y (�o�C�g�P��)
			&offsets						//�I�t�Z�b�g�l : ���_�o�b�t�@�[���̐擪�̗v�f�ƁA�g�p�����ŏ��̗v�f�Ƃ̊Ԋu
		);

		//�C���f�b�N�X�o�b�t�@��ݒ�
		if(auto indexBuffer = renderer->GetIndexBuffer())
			g_pImmedicateContext->IASetIndexBuffer(
				indexBuffer,
				DXGI_FORMAT_R32_UINT,
				0
			);

		//�v���~�e�B�u �^�C�v����уf�[�^�̏����Ɋւ�������o�C���h 
		renderer->SetPrimitiveTopology(g_pImmedicateContext);

		//�`��
		renderer->OnDraw(g_pImmedicateContext);

	}

	//�����_�����O���ꂽ�C���[�W����ʂɕ`�悷��
	g_pSwapChain->Present(0, 0);
}

//
// �e�탊�\�[�X��j������B
//
void Render::CleanupDevice() {

	//�f�o�C�X�R���e�L�X�g������̐ݒ�Ƀ��Z�b�g
	if (g_pImmedicateContext) g_pImmedicateContext->ClearState();

	//���\�[�X�̊J��
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