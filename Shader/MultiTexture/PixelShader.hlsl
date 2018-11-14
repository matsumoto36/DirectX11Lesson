
//�s�N�Z���V�F�[�_�[

//���_�V�F�[�_�[����󂯎��l
struct PS_IN {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;

};

Texture2D    mainTexture;	//�e�N�X�`���[
Texture2D    mainTexture2;	//�����ЂƂ�
Texture2D    mainTexture3;	//�����ЂƂ�
SamplerState mainSampler;	//�T���v���[
SamplerState mainSampler2;	//�T���v���[
SamplerState mainSampler3;	//�T���v���[

//�G���g���[�|�C���g
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