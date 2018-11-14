#pragma once

#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

//
// �V�F�[�_�[�Ə�������肷��N���X
//
class Material {

	const GeneratedShader* _generatedShader = nullptr;	//�V�F�[�_�[�̊e�f�[�^
	vector<ShaderData*> _shaderDataSet;		//[0] : vertex, [1] : pixel

public:

	Material() {

	}

	Material(const wstring &shaderName) {

		_generatedShader = Shader::FindShader(shaderName);
		
		auto variables = _generatedShader->GetVertexShaderVariables();
		for (size_t i = 0; i < variables.size(); i++) {
			_shaderDataSet
				.push_back(new ShaderData(*variables[i]));
		}
	}

	~Material() {
		
		for (auto shaderData : _shaderDataSet) {
			if (shaderData) delete shaderData;
		}
		_shaderDataSet.clear();

	}

	// �V�F�[�_�[�̖��O���擾����
	const wstring GetShaderName() {
		return _generatedShader->GetName();
	}

	// �V�F�[�_�[���f�o�C�X�Ɋ��蓖�Ă�
	bool SetShader(ID3D11DeviceContext &deviceContext) const {

		deviceContext.VSSetShader(_generatedShader->GetVertexShader(), NULL, 0);
		deviceContext.PSSetShader(_generatedShader->GetPixelShader(), NULL, 0);

		return true;
	}

	// ���̓A�Z���u���[�X�e�[�W�ɓ��̓��C�A�E�g�I�u�W�F�N�g���o�C���h����
	void SetInputLayout(ID3D11DeviceContext &deviceContext) const {
		deviceContext.IASetInputLayout(_generatedShader->GetInputLayout());
	}

	// �R���X�^���g�o�b�t�@���X�V����
	bool UpdateConstantBuffer(ID3D11DeviceContext &) const;
	// �f�o�C�X�Ƀo�b�t�@���Z�b�g����
	bool SetConstantBuffer(ID3D11DeviceContext &) const;
	// �e�N�X�`�����X�V����
	bool UpdateShaderResourceView(ID3D11DeviceContext &) const;
	// �T���v���[���X�V����
	bool UpdateSampler(ID3D11DeviceContext &) const;
	

	const float GetFloat(const string &) const;
	bool SetFloat(const string &, const float) const;

	const Vector2 GetFloat2(const string &) const;
	bool SetFloat2(const string &, const Vector2) const;

	const Vector3 GetFloat3(const string &) const;
	bool SetFloat3(const string &, const Vector3) const;

	const XMMATRIX GetMatrix(const string &) const;
	bool SetMatrix(const string &, const XMMATRIX) const;

	const Texture* GetTexture(const string &) const;
	bool SetTexture(const string &, Texture &);

private:

	// �f�[�^�^�C�v���w�肵�Ď����Ă���
	template<typename T>
	const T GetValue(const string &, D3D_SHADER_VARIABLE_TYPE targetType) const;

	// �f�[�^�^�C�v���w�肵�ăZ�b�g����
	template<typename T>
	const bool SetValue(const string &, const T value, D3D_SHADER_VARIABLE_TYPE targetType) const;

};