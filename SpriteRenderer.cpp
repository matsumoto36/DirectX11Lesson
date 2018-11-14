#include "SpriteRenderer.h"

void SpriteRenderer::Init() {

	//���_�o�b�t�@�̍쐬
	D3D11_BUFFER_DESC vertexDesc;
	ZeroMemory(&vertexDesc, sizeof(vertexDesc));
	vertexDesc.Usage = D3D11_USAGE_DEFAULT;						//�o�b�t�@�[�őz�肳��Ă���ǂݍ��݂���я������݂̕��@������
	vertexDesc.ByteWidth = polygon->GetVertex().size() * sizeof(Vertex);	//�o�b�t�@�[�̃T�C�Y (�o�C�g�P��)
	vertexDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;			//�o�b�t�@�[���ǂ̂悤�Ƀp�C�v���C���Ƀo�C���h���邩������
	vertexDesc.CPUAccessFlags = 0;								//CPU�A�N�Z�X�̃t���O
	vertexDesc.MiscFlags = 0;
	vertexDesc.StructureByteStride = 0;

	//�T�u���\�[�X�̏������Ɏg�p�����f�[�^���w��
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = &polygon->GetVertex()[0];							//�������f�[�^�ւ̃|�C���^
	InitData.SysMemPitch = 0;									//�e�N�X�`���[�ɂ���1�{�̐��̐�[����ׂ̐��܂ł̋��� (�o�C�g�P��)
	InitData.SysMemSlicePitch = 0;								//1�̐[�x���x���̐�[����ׂ̐[�x���x���܂ł̋��� (�o�C�g�P��) 

	auto hr = _device->CreateBuffer(
		&vertexDesc,				//�o�b�t�@�[�̃|�C���^
		&InitData,					//�������f�[�^�ւ̃|�C���^
		&_vertexBuffer				//�쐬�����o�b�t�@�[�ւ̃|�C���^
	);

	//�C���f�b�N�X�o�b�t�@�̍쐬
	auto indices = polygon->GetIndices();
	auto size = sizeof(indices);

	D3D11_BUFFER_DESC indicesDesc;
	ZeroMemory(&indicesDesc, sizeof(indicesDesc));
	indicesDesc.ByteWidth = size;
	indicesDesc.Usage = D3D11_USAGE_DEFAULT;
	indicesDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indicesDesc.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA indicesData;
	ZeroMemory(&indicesData, sizeof(indicesData));
	indicesData.pSysMem = &indices[0];

	hr = _device->CreateBuffer(&indicesDesc, &indicesData, &_indicesBuffer);



}
