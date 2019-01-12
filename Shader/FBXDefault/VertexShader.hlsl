// 受け取る頂点データの値
struct VS_IN {
	float4 pos : POSITION0;
	float4 col : COLOR0;
	float3 normal : NORMAL0;
	float2 uv  : TEXCOORD0;
};

// ピクセルシェーダーに送る値
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
	float3 normal : NORMAL0;
};

// 座標行列データを受け取る
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

	float3 n = mul(input.normal, World).xyz;
	output.normal = normalize(n);

	output.uv = input.uv;
	return output;
}