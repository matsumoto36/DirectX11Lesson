#include "Material.h"


bool Material::UpdateConstantBuffer(ID3D11DeviceContext &deviceContext) const {

	auto variables = _generatedShader->GetVertexShaderVariables();
	
	for (size_t i = 0; i < variables.size(); i++) {

		auto slots = variables[i]->GetConstantBufferSlots();
		for (size_t j = 0; j < slots.size(); j++) {
		
			deviceContext.UpdateSubresource(
				slots[j].Buffer, 0, nullptr, &_shaderDataSet[i]->CBData[j][0], 0, 0);
		}
	}

	return true;
}

bool Material::SetConstantBuffer(ID3D11DeviceContext &deviceContext) const {

	auto vsSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Vertex)]
		->GetConstantBufferSlots();

	for (size_t i = 0; i < vsSlots.size(); i++) {
		deviceContext.VSSetConstantBuffers(i, 1, &vsSlots[i].Buffer);
	}

	auto psSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Pixel)]
		->GetConstantBufferSlots();

	for (size_t i = 0; i < psSlots.size(); i++) {
		deviceContext.PSSetConstantBuffers(i, 1, &psSlots[i].Buffer);
	}

	return true;
}

bool Material::UpdateShaderResourceView(ID3D11DeviceContext &deviceContext) const {

	auto vsSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Vertex)]
		->GetShaderResourceSlots();

	for (auto slot : vsSlots) {

		auto texture = _shaderDataSet[static_cast<int>(ShaderStage::Vertex)]->Textures[slot.Name];
		if (!texture) continue;
		auto resourceView = texture->resourceView;
		if (!resourceView) continue;

		deviceContext.VSSetShaderResources(
			slot.Desc.BindPoint,
			slot.Desc.BindCount,
			&resourceView);
	}

	auto psSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Pixel)]
		->GetShaderResourceSlots();

	for (auto slot : psSlots) {

		auto texture = _shaderDataSet[static_cast<int>(ShaderStage::Pixel)]->Textures[slot.Name];
		if (!texture) continue;
		auto resourceView = texture->resourceView;
		if (!resourceView) continue;

		deviceContext.PSSetShaderResources(
			slot.Desc.BindPoint,
			slot.Desc.BindCount,
			&resourceView);
	}

	return true;
}

bool Material::UpdateSampler(ID3D11DeviceContext &deviceContext) const {

	auto vsSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Vertex)]
		->GetSamplerSlots();

	for (auto slot : vsSlots) {

		auto texture = _shaderDataSet[static_cast<int>(ShaderStage::Vertex)]->Textures[slot.Name];
		if (!texture) continue;
		auto sampler = texture->resourceView;
		if (!sampler) continue;

		deviceContext.VSSetShaderResources(
			slot.Desc.BindPoint,
			slot.Desc.BindCount,
			&sampler);
	}

	auto psSlots = _generatedShader
		->GetVertexShaderVariables()[static_cast<int>(ShaderStage::Pixel)]
		->GetSamplerSlots();

	for (auto slot : psSlots) {

		auto texture = _shaderDataSet[static_cast<int>(ShaderStage::Pixel)]->Textures[slot.Name];
		if (!texture) continue;
		auto sampler = texture->resourceView;
		if (!sampler) continue;

		deviceContext.PSSetShaderResources(
			slot.Desc.BindPoint,
			slot.Desc.BindCount,
			&sampler);
	}

	return true;
}

const float Material::GetFloat(const string &name) const {
	return GetValue<float>(name, D3D_SVT_FLOAT);
}
bool Material::SetFloat(const string &name, const float value) const {
	return SetValue<float>(name, value, D3D_SVT_FLOAT);
}


const Vector2 Material::GetFloat2(const string &name) const {
	return GetValue<Vector2>(name, D3D_SVT_FLOAT);
}
bool Material::SetFloat2(const string &name, const Vector2 value) const {
	return SetValue<Vector2>(name, value, D3D_SVT_FLOAT);
}

const Vector3 Material::GetFloat3(const string &name) const {
	return GetValue<Vector3>(name, D3D_SVT_FLOAT);
}
bool Material::SetFloat3(const string &name, const Vector3 value) const {
	return SetValue<Vector3>(name, value, D3D_SVT_FLOAT);
}

const XMMATRIX Material::GetMatrix(const string &name) const {
	return GetValue<XMMATRIX>(name, D3D_SVT_FLOAT);
}
bool Material::SetMatrix(const string &name, const XMMATRIX value) const {
	return SetValue<XMMATRIX>(name, value, D3D_SVT_FLOAT);
}

const Texture* Material::GetTexture(const string &name) const {

	for (auto shaderData : _shaderDataSet) {
		for (auto texture : shaderData->Textures) {
			if (texture.first != name) continue;
			return texture.second;
		}
	}

	return nullptr;
}

bool Material::SetTexture(const string &name, Texture &texture) {

	for (auto shaderData : _shaderDataSet) {
		for (auto &tex : shaderData->Textures) {
			if (tex.first != name) continue;
			tex.second = &texture;
		}
	}

	return false;
}

template<typename T>
const T Material::GetValue(const string &name, D3D_SHADER_VARIABLE_TYPE targetType) const {
	
	ConstantVariable cv;

	auto variables = _generatedShader->GetVertexShaderVariables();
	for (size_t i = 0; i < variables.size(); i++) {

		if (!variables[i]->GetConstantBufferVariable(name, cv)) continue;

		D3D11_SHADER_TYPE_DESC desc;
		cv.Type->GetDesc(&desc);
		if (desc.Type != targetType) continue;

		auto dataStart = &_shaderDataSet[i]->CBData[cv.Slot][cv.Desc.StartOffset];
		T data = T();
		//データからTとしてコピーしてくる
		copy(dataStart, dataStart + sizeof(T), (UCHAR*)&data);
		return data;

	}

	return T();

}

template<typename T>
const bool Material::SetValue(const string &name, const T value, D3D_SHADER_VARIABLE_TYPE targetType) const {

	auto variables = _generatedShader->GetVertexShaderVariables();
	for (size_t i = 0; i < variables.size(); i++) {
		if (variables[i]->SetConstantBufferVariable(name, (UCHAR*)&value, _shaderDataSet[i]->CBData, targetType))
			return true;
	}

	return false;

}