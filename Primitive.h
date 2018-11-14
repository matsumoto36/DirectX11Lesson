#pragma once

#include <vector>

using namespace std;

//頂点のデータ
struct Vertex {
	float pos[3];
	float col[4];
	float uv[2];
};

class Mesh;

enum class PrimitiveType {
	Polygon,
	Star,
};

class Primitive {

	const static vector<Mesh*> meshData;
	const static vector<Vertex> polygon;
	const static vector<Vertex> star;

public:
	Primitive();
	~Primitive();

	static Mesh* GetPrimitiveMesh(PrimitiveType type);
};

