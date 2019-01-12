#pragma once

#include <vector>
#include <memory>
#include <fbxsdk.h>
#include <d3d11.h>					//DirectX11
#include <DirectXMath.h>

#include <unordered_map>
#include "Mesh.h"
#include "Primitive.h"

#pragma comment(lib, "d3d11.lib")	//�����N���邽�߂ɕK�v

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

	// �ǂݍ��܂ꂽ���b�V�����擾����
	const Mesh* GetMesh(string& name) {
		return _modelData[name];
	}

};