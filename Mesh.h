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

	vector<Vertex> _vertex;		//モデルの頂点データ
	vector<int> _indices;		//モデルの三角形の順のデータ

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

	// 頂点カラーを設定する
	void SetColor(float r, float g, float b, float a) {

		for (size_t i = 0; i < _vertex.size(); i++) {
			_vertex[i].col[0] = r;
			_vertex[i].col[1] = g;
			_vertex[i].col[2] = b;
			_vertex[i].col[3] = a;
		}

	}

	// uvの値をセットする
	void SetUV(size_t index, float u, float v) {

		if (index < 0 || index >= _vertex.size()) {
			cout << "[Error] failed Set UV at " << index << "." << endl;
			return;
		}

		_vertex[index].uv[0] = u;
		_vertex[index].uv[1] = v;
	}

};

