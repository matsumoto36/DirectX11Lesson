
//�s�N�Z���V�F�[�_�[
cbuffer Properties {
	float Ratio;
}

Texture2D MagicTexture;	
Texture2D MaskTexture;	
Texture2D BGTexture;	

SamplerState mainSampler;	//�T���v���[


//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

//�G���g���[�|�C���g
float4 main(PS_IN input) : SV_TARGET
{
	float4 col = MagicTexture.Sample(mainSampler, input.uv);
	float4 mask = MaskTexture.Sample(mainSampler, input.uv);
	float4 back = BGTexture.Sample(mainSampler, input.uv);

	float4 m = mask + Ratio > 1 ? 1 : 0;
	return back + (col * m);
}