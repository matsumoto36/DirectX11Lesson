#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "Texture.h"

using namespace std;

//
// コンスタントバッファ内の変数
//
struct ConstantVariable {
	
	string Name;						//変数名
	size_t Slot;						
	ID3D11ShaderReflectionVariable* Variable;

	D3D11_SHADER_VARIABLE_DESC Desc;
	ID3D11ShaderReflectionConstantBuffer* Buffer;
	ID3D11ShaderReflectionType* Type;

	ConstantVariable() {
		ZeroMemory(&Desc, sizeof Desc);
	}

	ConstantVariable(size_t slot, ID3D11ShaderReflectionVariable* const &variable)
		: Slot(slot), Variable(variable) {
		
		variable->GetDesc(&Desc);
		Name = Desc.Name;
		Buffer = variable->GetBuffer();
		Type = variable->GetType();
	}

};

//
// 一つのコンスタントバッファの内容
//
struct ConstantBufferSlot {

	ID3D11Buffer* const Buffer;				//コンスタントバッファ
	vector<ConstantVariable> Variables;		//バッファ内の変数リスト
	const size_t BufferSize;				//バッファのサイズ

	ConstantBufferSlot(ID3D11Buffer* &buffer, size_t size)
		: Buffer(buffer), BufferSize(size) {}

	// メモリに内容をセットする
	void SetValue(size_t offset, size_t size, const UCHAR *dataStart, vector<UCHAR> &dest) {
		copy(dataStart, dataStart + size, &dest[offset]);
	}

};

struct ShaderResourceSlot {

	string Name;
	D3D11_SHADER_INPUT_BIND_DESC Desc;

};


//
// 一つのシェーダーに含まれる変数
//
class ShaderVariable {

	vector<ConstantBufferSlot> _constantBufferSlots;
	vector<ShaderResourceSlot> _shaderResourceSlots;
	vector<ShaderResourceSlot> _samplerSlots;

public:

	ShaderVariable(ID3D11Device &device, ID3D11ShaderReflection & reflection) {
		Initialize(device, reflection);
	}

	// リフレクションを使って各メンバを設定する
	bool Initialize(ID3D11Device &, ID3D11ShaderReflection &);


	const vector<ConstantBufferSlot> GetConstantBufferSlots() const {
		return _constantBufferSlots;
	}
	const vector<ShaderResourceSlot> GetShaderResourceSlots() const {
		return _shaderResourceSlots;
	}
	const vector<ShaderResourceSlot> GetSamplerSlots() const {
		return _samplerSlots;
	}


	// 名前からコンスタントバッファの変数を取得する
	bool GetConstantBufferVariable(const string &, ConstantVariable &) const;

	// コンスタントバッファの値を指定した場所に書き込む
	bool SetConstantBufferVariable(const string &, const UCHAR* , vector<vector<UCHAR>> &, D3D_SHADER_VARIABLE_TYPE);


private:

	HRESULT AddConstantBufferSlot(ID3D11Device &, size_t);

	void AddConstantBufferVariable(size_t, ID3D11ShaderReflectionVariable* const &);

	void AddShaderResourceSlot(const D3D11_SHADER_INPUT_BIND_DESC &desc) {
		_shaderResourceSlots.push_back(ShaderResourceSlot{ desc.Name, desc });
	}

	void AddSamplerSlot(const D3D11_SHADER_INPUT_BIND_DESC &desc) {
		_samplerSlots.push_back(ShaderResourceSlot{ desc.Name, desc });
	}
};

//
// シェーダーに送るためのデータ群
//
struct ShaderData {

	vector<vector<UCHAR>> CBData;
	unordered_map<string, Texture*> Textures;
	unordered_map<string, Texture*> Samplers;

	ShaderData(const ShaderVariable variable) {
		
		auto CBSlots = variable.GetConstantBufferSlots();
		CBData.resize(CBSlots.size());
		for (size_t i = 0; i < CBData.size(); i++) {
			CBData[i].resize(CBSlots[i].BufferSize);
		}

		for (auto slots : variable.GetShaderResourceSlots()) {
			Textures.emplace(slots.Name, nullptr);
		}

		for (auto slots : variable.GetSamplerSlots()) {
			Samplers.emplace(slots.Name, nullptr);
		}
	}
};
