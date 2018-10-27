
//頂点シェーダー

//GPUから受け取る頂点バッファ
struct VS_IN {

	//D3D11_INPUT_ELEMENT_DESCで定義したセマンティクス名・インデックス番号
	float4 pos : POSITION0;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

//頂点シェーダーからピクセルシェーダーに渡す値
struct VS_OUT {
	//すでに頂点シェーダーで処理されているので、システム上で使う値としてSV_POSITIONを渡す
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

//座標行列データを受け取る
cbuffer ConstantBuffer : register(b0) {
	matrix World;		//ワールド座標行列
	matrix View;		//ビュー座標行列
	matrix Projection;	//プロジェクション座標行列
}

VS_OUT main(VS_IN input) {

	VS_OUT output;

	//現在の座標とワールド座標行列で行列の乗算を行う
	output.pos = mul(input.pos, World);
	//上記の値とビュー座標行列で行列の乗算を行う
	output.pos = mul(output.pos, View);
	//上記の値とプロジェクション座標行列で行列の乗算を行う
	output.pos = mul(output.pos, Projection);
	output.uv = input.uv;

	return output;
}