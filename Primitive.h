#pragma once

#include <DirectXMath.h>
#include <vector>

using namespace std;
using namespace DirectX;
//頂点のデータ
struct Vertex {
	XMFLOAT4 pos;
	XMFLOAT4 col;
	XMFLOAT3 normal;
	XMFLOAT2 uv;
};

class Mesh;

enum class PrimitiveType {
	Polygon,
	Box,
	Star,
};

class Primitive {

	const static vector<Mesh*> meshData;
	//const static vector<Vertex> polygon;
	//const static vector<Vertex> star;

public:
	Primitive();
	~Primitive();

	static const Mesh* CreatePrimitiveMesh(PrimitiveType type);
};

