
//�s�N�Z���V�F�[�_�[

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

cbuffer Property {
	float2 Count;
	float2 Offset;
};

Texture2D    MainTexture; //�e�N�X�`���[
SamplerState mainSampler; //�T���v���[

//�G���g���[�|�C���g
float4 main(PS_IN input) : SV_TARGET
{
	float2 uv = input.uv * Count + Offset;
	return MainTexture.Sample(mainSampler, uv);
}