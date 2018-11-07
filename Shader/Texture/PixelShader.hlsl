
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    mainTexture : register(t0); //テクスチャー
SamplerState mainSampler : register(s0); //サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	return mainTexture.Sample(mainSampler, input.uv);
}