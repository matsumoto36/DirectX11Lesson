
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    mainTexture;	//テクスチャー
Texture2D    mainTexture2;	//もうひとつの
Texture2D    mainTexture3;	//もうひとつ
SamplerState mainSampler;	//サンプラー
SamplerState mainSampler2;	//サンプラー
SamplerState mainSampler3;	//サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	if (input.uv.x < 0.33f) {
		return mainTexture.Sample(mainSampler, input.uv);
	}
	else if(input.uv.x < 0.66f){
		return mainTexture2.Sample(mainSampler2, input.uv);
	}
	else {
		return mainTexture3.Sample(mainSampler3, input.uv);
	}
}