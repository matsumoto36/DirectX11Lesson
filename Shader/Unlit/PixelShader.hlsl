
//�s�N�Z���V�F�[�_�[
cbuffer Properties {
	float4 MainColor;
}

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

//�G���g���[�|�C���g
float4 main(PS_IN input) : SV_TARGET
{
	return MainColor;
}