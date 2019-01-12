
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

cbuffer Property {
	float2 Count;
	float2 Offset;
};

Texture2D    MainTexture; //テクスチャー
SamplerState mainSampler; //サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	float2 uv = input.uv * Count + Offset;
	return MainTexture.Sample(mainSampler, uv);
}