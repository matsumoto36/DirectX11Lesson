
//�s�N�Z���V�F�[�_�[
cbuffer Properties {
	float3 Light;		//���C�g�̕���
};

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
	float3 normal : NORMAL0;
};

Texture2D    MainTexture; //�e�N�X�`���[
Texture2D	 NormalTexture;
SamplerState mainSampler; //�T���v���[

//�G���g���[�|�C���g
float4 main(PS_IN input) : SV_TARGET
{
	//float3 normal = 2 * NormalTexture.Sample(mainSampler, input.uv).xyz - 1;
	//normal = normalize(normal);
	//float3 bright = saturate(dot(normal, Light));
	//return MainTexture.Sample(mainSampler, input.uv) * float4(bright, 1);



	//float4 col = saturate(dot(input.normal, Light));
	//col = col * 0.7f + 0.3f;
	//col.a = 1.0f;
	//return MainTexture.Sample(mainSampler, input.uv) * col;

	return float4(1, 1, 1, 1);
}