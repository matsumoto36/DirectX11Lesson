
//���_�V�F�[�_�[

//GPU����󂯎�钸�_�o�b�t�@
struct VS_IN {

	//D3D11_INPUT_ELEMENT_DESC�Œ�`�����Z�}���e�B�N�X���E�C���f�b�N�X�ԍ�
	float4 pos : POSITION0;
	float4 col : COLOR0;
	float2 uv  : TEXCOORD0;
};

//���_�V�F�[�_�[����s�N�Z���V�F�[�_�[�ɓn���l
struct VS_OUT {
	//���łɒ��_�V�F�[�_�[�ŏ�������Ă���̂ŁA�V�X�e����Ŏg���l�Ƃ���SV_POSITION��n��
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
};

//���W�s��f�[�^���󂯎��
cbuffer ConstantBuffer : register(b0) {
	matrix World;		//���[���h���W�s��
	matrix View;		//�r���[���W�s��
	matrix Projection;	//�v���W�F�N�V�������W�s��
}

VS_OUT main(VS_IN input) {

	VS_OUT output;

	//���݂̍��W�ƃ��[���h���W�s��ōs��̏�Z���s��
	output.pos = mul(input.pos, World);
	//��L�̒l�ƃr���[���W�s��ōs��̏�Z���s��
	output.pos = mul(output.pos, View);
	//��L�̒l�ƃv���W�F�N�V�������W�s��ōs��̏�Z���s��
	output.pos = mul(output.pos, Projection);
	output.uv = input.uv;

	return output;
}