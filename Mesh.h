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

	vector<Vertex>				_vertex;		//���f���̒��_�f�[�^
	vector<int>					_indices;		//���f���̎O�p�`�̏��̃f�[�^

	D3D11_PRIMITIVE_TOPOLOGY	_topology;		//�f�[�^�̏���

public:

	Mesh(vector<Vertex> vertex, vector<int> indices, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP)
		: _vertex(vertex), _indices(indices), _topology(topology) {}

	Mesh(const Mesh &mesh) 
		: _vertex(mesh._vertex), _indices(mesh._indices), _topology(mesh._topology) {}

	~Mesh() {}

	const vector<Vertex>& GetVertex() const {
		return _vertex;
	}

	const vector<int>& GetIndices() const {
		return _indices;
	}

	const D3D11_PRIMITIVE_TOPOLOGY& GetPrimitiveTopology() const {
		return _topology;
	}

};

