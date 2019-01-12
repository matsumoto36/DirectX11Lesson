
//�s�N�Z���V�F�[�_�[

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    MainTexture;	//�e�N�X�`���[
Texture2D    MainTexture2;	//�����ЂƂ�
Texture2D    MainTexture3;	//�����ЂƂ�

SamplerState mainSampler;	//�T���v���[

//�G���g���[�|�C���g
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