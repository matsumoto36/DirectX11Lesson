// �󂯎�钸�_�f�[�^�̒l
struct VS_IN {
	float4 pos : POSITION0;
	float4 col : COLOR0;
	float3 normal : NORMAL0;
	float2 uv  : TEXCOORD0;
};

// �s�N�Z���V�F�[�_�[�ɑ���l
struct VS_OUT {
	float4 pos : SV_POSITION;
	float2 uv  : TEXCOORD0;
	float3 normal : NORMAL0;
};

// ���W�s��f�[�^���󂯎��
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

	float3 n = mul(input.normal, World).xyz;
	output.normal = normalize(n);

	output.uv = input.uv;
	return output;
}