
//ピクセルシェーダー

//頂点シェーダーから受け取る値
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
	float2 size  : TEXCOORD1;

};

Texture2D    mainTexture : register(t0); //テクスチャー
SamplerState mainSampler : register(s0); //サンプラー

//エントリーポイント
float4 main(PS_IN input) : SV_TARGET
{
	//1
	//return float4(1, 0, 0, 1);
	
	//2
	//return mainTexture.Sample(mainSampler, input.uv);

	//3
	//float brightMul = 2.0f;
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.rgb *= bright;
	//return col;

	//4
	//float brightMul = 0.5f;
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.rgb *= bright;
	//return col;

	//5
	//float redBright = 2.0f;
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.r *= redBright;
	//return col;

	//6
	//グレースケール
	//float3 gray = float3(0.298912f, 0.586611f, 0.114478f);
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.rgb = dot(col.rgb, gray);
	//return col;

	//7
	//float blueBright = 2.0f;
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.b *= input.uv.x = > 0.5f ? blueBright : 1.0f;
	//return col;

	//8
	//float4 col = mainTexture.Sample(mainSampler, input.uv);
	//col.rgb = 1 - col.rgb;
	//return col;

	//9 , 10
	//float2 textureSize = float2(input.size.x, input.size.y);

	//float blur = 1.0f;
	//float blurLoop = 3;
	//float4 col = float4(0.0f, 0.0f, 0.0f, 0.0f);

	//for (int i = 1; i <= blurLoop; i++) {
	//	col += mainTexture.Sample(mainSampler, input.uv + (float2(blur * i, blur * i) / textureSize));
	//	col += mainTexture.Sample(mainSampler, input.uv + (float2(blur * i, blur *  -i) / textureSize));
	//	col += mainTexture.Sample(mainSampler, input.uv + (float2(blur * -i, blur * i) / textureSize));
	//	col += mainTexture.Sample(mainSampler, input.uv + (float2(blur * -i, blur * -i) / textureSize));
	//}
	//col /= blurLoop * 4;

	return float4(0, 0, 0, 1);

}