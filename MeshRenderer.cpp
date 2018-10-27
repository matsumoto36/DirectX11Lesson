#include "MeshRenderer.h"

void MeshRenderer::Init() {

	transform = XMMatrixIdentity();
	pVertexBuffer = nullptr;
	pTexture = nullptr;

	//�V�F�[�_�[��ݒ�
	SetShader(L"Unlit");

	//�o�b�t�@�[���\�[�X�̒�`
	D3D11_BUFFER_DESC descBuffer;
	ZeroMemory(&descBuffer, sizeof(descBuffer));
	descBuffer.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@������
	descBuffer.ByteWidth = mesh->GetModelData().size() * sizeof(Vertex);	//�o�b�t�@�[�̃T�C�Y (�o�C�g�P��)
	descBuffer.BindFlags = D3D11_BIND_VERTEX_BUFFER;			//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C���Ƀo�C���h���邩������
	descBuffer.CPUAccessFlags = 0;								//CPU�A�N�Z�X�̃t���O
																//�T�u���\�[�X�̏������Ɏg�p�����f�[�^���w��
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &mesh->GetModelData()[0];							//�������f�[�^�ւ̃|�C���^
	InitData.SysMemPitch = 0;									//�e�N�X�`���[�ɂ���1�{�̐��̐�[����ׂ̐��܂ł̋��� (�o�C�g�P��)
	InitData.SysMemSlicePitch = 0;								//1�̐[�x���x���̐�[����ׂ̐[�x���x���܂ł̋��� (�o�C�g�P��) 

	//���_�o�b�t�@�[�̍쐬
	auto hr = device->CreateBuffer(
		&descBuffer,				//�o�b�t�@�[�̃|�C���^
		&InitData,					//�������f�[�^�ւ̃|�C���^
		&pVertexBuffer				//�쐬�����o�b�t�@�[�ւ̃|�C���^
	);

}
