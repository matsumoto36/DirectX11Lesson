#include "SpriteRenderer.h"

void SpriteRenderer::Init() {

	//頂点バッファの作成
	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;						//バッファーで想定されている読み込みおよび書き込みの方法を識別
	vertexDesc.ByteWidth = polygon->GetVertex().size() * sizeof(Vertex);	//バッファーのサイズ (バイト単位)
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;			//バッファーをどのようにパイプラインにバインドするかを識別
	vertexDesc.CPUAccessFlags = 0;								//CPUアクセスのフラグ
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	//サブリソースの初期化に使用されるデータを指定
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &polygon->GetVertex()[0];							//初期化データへのポインタ
	InitData.SysMemPitch = 0;									//テクスチャーにある1本の線の先端から隣の線までの距離 (バイト単位)
	InitData.SysMemSlicePitch = 0;								//1つの深度レベルの先端から隣の深度レベルまでの距離 (バイト単位) 

	auto hr = _device->CreateBuffer(
		&vertexDesc,				//バッファーのポインタ
		&InitData,					//初期化データへのポインタ
		&_vertexBuffer				//作成されるバッファーへのポインタ
	);

	//インデックスバッファの作成
	auto indices = polygon->GetIndices();
	auto size = sizeof(indices);

	D3D11_BUFFER_DESC indicesDesc;
	ZeroMemory(&indicesDesc, sizeof(indicesDesc));
	indicesDesc.ByteWidth = size;
	indicesDesc.Usage = D3D11_USAGE_DEFAULT;
	indicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indicesDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indicesData;
	ZeroMemory(&indicesData, sizeof(indicesData));
	indicesData.pSysMem = &indices[0];

	hr = _device->CreateBuffer(&indicesDesc, &indicesData, &_indicesBuffer);



}
