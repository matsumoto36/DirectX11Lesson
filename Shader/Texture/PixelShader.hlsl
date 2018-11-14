
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

Texture2D    mainTexture; //テクスチャー
SamplerState mainSampler; //サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{

	if (input.uv.x < 0.5f) {
		//return mainTexture.Sample(mainSampler, input.uv);
		return float4(0, 0, 1, 1);
	}
	else {
		return float4(1, 1, 1, 1);
	}
	
}