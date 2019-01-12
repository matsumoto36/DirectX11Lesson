
//ピクセルシェーダー
cbuffer Properties {
	float4 MainColor;
}

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	return MainColor;
}