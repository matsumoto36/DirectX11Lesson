
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    MainTexture;	//テクスチャー
Texture2D    MainTexture2;	//もうひとつの
Texture2D    MainTexture3;	//もうひとつ

SamplerState mainSampler;	//サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	if (input.uv.x < 0.33f) {
		return MainTexture.Sample(mainSampler, input.uv);
	}
	else if(input.uv.x < 0.66f){
		return MainTexture2.Sample(mainSampler, input.uv);
	}
	else {
		return MainTexture3.Sample(mainSampler, input.uv);
	}
}