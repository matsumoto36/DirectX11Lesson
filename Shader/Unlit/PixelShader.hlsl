
//ピクセルシェーダー
cbuffer Properties {
	float3 Red;
	float3 Green;
	float3 Blue;
	float3 White;
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

	float4 color = float4(0, 0, 0, 1);

	if (input.uv.x < 0.5f) {
		if (input.uv.y < 0.5f)
			color.rgb = Red;
		else
			color.rgb = Green;
	} else {
		if (input.uv.y < 0.5f)
			color.rgb = Blue;
		else
			color.rgb = White;
	}

	return color;
	//return float4(Gray, Gray, Gray, 1);
	//return float4(1, 1, 1, 1);
	//return input.col;
}