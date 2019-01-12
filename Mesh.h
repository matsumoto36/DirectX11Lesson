#pragma once

#include <d3d11.h>					//DirectX11
#include <DirectXColors.h>			//DirectX::Colorsを利用するために必要
#include <d3dcompiler.h>
#include <iostream>

#include <vector>
#include "Texture.h"
#include "Primitive.h"
#include "Shader.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要
#pragma comment(lib, "d3dCompiler.lib")

using namespace std;
using namespace DirectX;

//
// モデルのデータ
//
class Mesh {

	vector<Vertex>				_vertex;		//モデルの頂点データ
	vector<int>					_indices;		//モデルの三角形の順のデータ

	D3D11_PRIMITIVE_TOPOLOGY	_topology;		//データの順序

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

