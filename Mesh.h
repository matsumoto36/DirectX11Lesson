#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colors�𗘗p���邽�߂ɕK�v
#include <d3dcompiler.h>
#include <iostream>

#include <vector>
#include "Texture.h"
#include "Primitive.h"
#include "Shader.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// ���f���̃f�[�^
//
class Mesh {

	vector<Vertex>	modelData;		//���f���̒��_�f�[�^

public:

	Mesh(const vector<Vertex> modelData) : modelData(modelData) {

	}

	Mesh(PrimitiveType type) : modelData(Primitive::GetPrimitiveVertex(type)) {

	}

	~Mesh() {}

	const vector<Vertex>& GetModelData() {
		return modelData;
	}

	// ���_�J���[��ݒ肷��
	void SetColor(float r, float g, float b, float a) {

		for (size_t i = 0; i < modelData.size(); i++) {
			modelData[i].col[0] = r;
			modelData[i].col[1] = g;
			modelData[i].col[2] = b;
			modelData[i].col[3] = a;
		}

	}

	// uv�̒l���Z�b�g����
	void SetUV(int index, float u, float v) {

		if (index < 0 || index >= modelData.size()) {
			cout << "[Error] failed Set UV at " << index << "." << endl;
			return;
		}

		modelData[index].uv[0] = u;
		modelData[index].uv[1] = v;
	}

};

