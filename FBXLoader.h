#pragma once

#include <vector>
#include <memory>
#include <fbxsdk.h>
#include <d3d11.h>					//DirectX11
#include <DirectXMath.h>

#include <unordered_map>
#include "Mesh.h"
#include "Primitive.h"

#pragma comment(lib, "d3d11.lib")	//リンクするために必要

using namespace std;
using namespace DirectX;
using namespace fbxsdk;

struct MeshVertex {
	XMFLOAT3 Pos;
};

class FBXLoader {

private:

	FbxManager* _manager;
	FbxScene* _scene;
	
	vector<FbxMesh*> _meshes;

	unordered_map<string, Mesh*> _modelData;


public:

	FBXLoader();
	~FBXLoader();

	// 読み込まれたメッシュを取得する
	const Mesh* GetMesh(string& name) {
		return _modelData[name];
	}

};