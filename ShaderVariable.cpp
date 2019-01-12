#include "ShaderVariable.h"


bool ShaderVariable::Initialize(ID3D11Device &device, ID3D11ShaderReflection &reflection) {
	
	D3D11_SHADER_DESC shaderDesc;
	reflection.GetDesc(&shaderDesc);

	//コンスタントバッファの読み取り
	for (size_t i = 0; i < shaderDesc.ConstantBuffers; i++) {
		auto cb = reflection.GetConstantBufferByIndex(i);
		D3D11_SHADER_BUFFER_DESC shaderBufferDesc;
		cb->GetDesc(&shaderBufferDesc);

		AddConstantBufferSlot(device, shaderBufferDesc.Size);
		for (size_t j = 0; j < shaderBufferDesc.Variables; j++) {
			AddConstantBufferVariable(i, cb->GetVariableByIndex(j));
		}
	}

	//シェーダーリソースの読み取り
	for (size_t i = 0; i < shaderDesc.BoundResources; i++) {

		D3D11_SHADER_INPUT_BIND_DESC desc;
		reflection.GetResourceBindingDesc(i, &desc);

		switch (desc.Type) {
			case D3D_SIT_TEXTURE:
				AddShaderResourceSlot(desc);
				break;
			case D3D_SIT_SAMPLER:
				AddSamplerSlot(desc);
				break;
		}
	}

	return true;
}

bool ShaderVariable::GetConstantBufferVariable(const string &name, ConstantVariable &outSlot) const {

	for (auto slot : _constantBufferSlots) {
		for (auto variable : slot.Variables) {
			if (name != variable.Name) continue;
			
			outSlot = variable;
			return true;
		}
	}

	return false;
}

bool ShaderVariable::SetConstantBufferVariable(const string &name, const UCHAR* dataStart, vector<vector<UCHAR>> &dest, D3D_SHADER_VARIABLE_TYPE targetType) {

	ConstantVariable cv;
	if (!GetConstantBufferVariable(name, cv)) return false;

	D3D11_SHADER_TYPE_DESC desc;
	cv.Type->GetDesc(&desc);
	if (desc.Type != targetType) return false;

	_constantBufferSlots[cv.Slot]
		.SetValue(cv.Desc.StartOffset, cv.Desc.Size, dataStart, dest[cv.Slot]);

	return true;
}

HRESULT ShaderVariable::AddConstantBufferSlot(ID3D11Device &device, size_t size) {

	D3D11_BUFFER_DESC desc = { 0 };
	desc.ByteWidth = size;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	ID3D11Buffer* buffer = nullptr;
	auto hr = device.CreateBuffer(&desc, nullptr, &buffer);

	if (FAILED(hr)) return hr;

	_constantBufferSlots.push_back(ConstantBufferSlot(buffer, size));

	return hr;
}

void ShaderVariable::AddConstantBufferVariable(size_t slotIndex, ID3D11ShaderReflectionVariable* const &variable) {

	if (slotIndex >= _constantBufferSlots.size()) return;

	_constantBufferSlots[slotIndex]
		.Variables
		.push_back(ConstantVariable(slotIndex, variable));
}