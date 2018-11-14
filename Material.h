#pragma once

#include <string>

#include "Vector2.h"
#include "Vector3.h"
#include "Shader.h"
#include "Texture.h"

using namespace std;

//
// シェーダーと情報をやり取りするクラス
//
class Material {

	const GeneratedShader* _generatedShader = nullptr;	//シェーダーの各データ
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

	// シェーダーの名前を取得する
	const wstring GetShaderName() {
		return _generatedShader->GetName();
	}

	// シェーダーをデバイスに割り当てる
	bool SetShader(ID3D11DeviceContext &deviceContext) const {

		deviceContext.VSSetShader(_generatedShader->GetVertexShader(), NULL, 0);
		deviceContext.PSSetShader(_generatedShader->GetPixelShader(), NULL, 0);

		return true;
	}

	// 入力アセンブラーステージに入力レイアウトオブジェクトをバインドする
	void SetInputLayout(ID3D11DeviceContext &deviceContext) const {
		deviceContext.IASetInputLayout(_generatedShader->GetInputLayout());
	}

	// コンスタントバッファを更新する
	bool UpdateConstantBuffer(ID3D11DeviceContext &) const;
	// デバイスにバッファをセットする
	bool SetConstantBuffer(ID3D11DeviceContext &) const;
	// テクスチャを更新する
	bool UpdateShaderResourceView(ID3D11DeviceContext &) const;
	// サンプラーを更新する
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

	// データタイプを指定して持ってくる
	template<typename T>
	const T GetValue(const string &, D3D_SHADER_VARIABLE_TYPE targetType) const;

	// データタイプを指定してセットする
	template<typename T>
	const bool SetValue(const string &, const T value, D3D_SHADER_VARIABLE_TYPE targetType) const;

};