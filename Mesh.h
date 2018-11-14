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

	vector<Vertex> _vertex;		//���f���̒��_�f�[�^
	vector<int> _indices;		//���f���̎O�p�`�̏��̃f�[�^

public:

	Mesh(vector<Vertex> vertex, vector<int> indices)
		: _vertex(vertex), _indices(indices) {}

	Mesh(const Mesh &mesh) 
		: _vertex(mesh._vertex), _indices(mesh._indices) {}

	//Mesh(PrimitiveType type) {
	//	auto mesh = Primitive::GetPrimitiveMesh(type)
	//}

	~Mesh() {}

	const vector<Vertex>& GetVertex() {
		return _vertex;
	}

	const vector<int>& GetIndices() {
		return _indices;
	}

	// ���_�J���[��ݒ肷��
	void SetColor(float r, float g, float b, float a) {

		for (size_t i = 0; i < _vertex.size(); i++) {
			_vertex[i].col[0] = r;
			_vertex[i].col[1] = g;
			_vertex[i].col[2] = b;
			_vertex[i].col[3] = a;
		}

	}

	// uv�̒l���Z�b�g����
	void SetUV(size_t index, float u, float v) {

		if (index < 0 || index >= _vertex.size()) {
			cout << "[Error] failed Set UV at " << index << "." << endl;
			return;
		}

		_vertex[index].uv[0] = u;
		_vertex[index].uv[1] = v;
	}

};

