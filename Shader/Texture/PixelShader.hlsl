
//�s�N�Z���V�F�[�_�[

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    mainTexture : register(t0); //�e�N�X�`���[
SamplerState mainSampler : register(s0); //�T���v���[

//�G���g���[�|�C���g
float4 main(PS_IN input) : SV_TARGET
{
	return mainTexture.Sample(mainSampler, input.uv);
}