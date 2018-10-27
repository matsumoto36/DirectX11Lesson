#include "MeshRenderer.h"

void MeshRenderer::Init() {

	transform = XMMatrixIdentity();
	pVertexBuffer = nullptr;
	pTexture = nullptr;

	//シェーダーを設定
	SetShader(L"Unlit");

	//バッファーリソースの定義
	D3D11_BUFFER_DESC descBuffer;
	ZeroMemory(&descBuffer, sizeof(descBuffer));
	descBuffer.Usage = D3D11_USAGE_DEFAULT;						//バッファーで想定されている読み込みおよび書き込みの方法を識別
	descBuffer.ByteWidth = mesh->GetModelData().size() * sizeof(Vertex);	//バッファーのサイズ (バイト単位)
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;			//バッファーをどのようにパイプラインにバインドするかを識別
	descBuffer.CPUAccessFlags = 0;								//CPUアクセスのフラグ
																//サブリソースの初期化に使用されるデータを指定
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &mesh->GetModelData()[0];							//初期化データへのポインタ
	InitData.SysMemPitch = 0;									//テクスチャーにある1本の線の先端から隣の線までの距離 (バイト単位)
	InitData.SysMemSlicePitch = 0;								//1つの深度レベルの先端から隣の深度レベルまでの距離 (バイト単位) 

	//頂点バッファーの作成
	auto hr = device->CreateBuffer(
		&descBuffer,				//バッファーのポインタ
		&InitData,					//初期化データへのポインタ
		&pVertexBuffer				//作成されるバッファーへのポインタ
	);

}
