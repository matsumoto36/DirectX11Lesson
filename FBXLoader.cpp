#include "FBXLoader.h"



FBXLoader::FBXLoader() :
	_manager(FbxManager::Create()),
	_scene(FbxScene::Create(_manager, "")) {
	
	FbxString fileName = "Resources/Model/Test2.FBX";

	auto importer = FbxImporter::Create(_manager, "");

	importer->Initialize(
		fileName.Buffer(),
		-1,
		_manager->GetIOSettings()
	);

	importer->Import(_scene);
	importer->Destroy();

	//座標軸を変換
	FbxAxisSystem::DirectX.ConvertScene(_scene);

	FbxGeometryConverter fgc(_manager);
	fgc.Triangulate(_scene, true);

	auto meshCount = _scene->GetSrcObjectCount<FbxMesh>();
	//メッシュの数だけ繰り返す
	for (auto i = 0; i < meshCount; ++i) {
		//メッシュデータを取得
		auto mesh = _scene->GetSrcObject<FbxMesh>(i);

		_meshes.push_back(mesh);
	}

	auto vertices = vector<Vertex>();
	auto indices = vector<int>();

	for (auto mesh : _meshes) {

		auto polygonCount = mesh->GetPolygonCount();

		//ポリゴンごと
		for (auto i = 0; i < polygonCount; ++i) {
			for (auto j = 0; j < 3; j++) {

				//インデックスデータ
				auto index = mesh->GetPolygonVertex(i, j);
				indices.push_back(index);

				Vertex v;

				//座標
				auto pos = mesh->GetControlPointAt(index);
				v.pos.x = pos[0];
				v.pos.y = pos[1];
				v.pos.z = pos[2];
				v.pos.w = 1.0f;

				//頂点カラー
				v.col = { 1.0f, 1.0f, 1.0f, 1.0f };

				//法線
				FbxVector4 normal;
				mesh->GetPolygonVertexNormal(i, j, normal);
				v.normal.x = normal[0];
				v.normal.y = normal[1];
				v.normal.z = normal[2];

				vertices.push_back(v);
			}
		}


		//UVを取得
		//頂点に格納されている全UVセットを名前で取得
		FbxStringList uvsetName;
		mesh->GetUVSetNames(uvsetName);
		auto name = uvsetName.GetStringAt(0);

		auto count = 0;
		for (auto i = 0; i < polygonCount; ++i) {
			for (auto j = 0; j < 3; j++) {

				FbxVector2 texCoord;
				bool unmapped;
				mesh->GetPolygonVertexUV(i, j, name, texCoord, unmapped);

				vertices[count].uv.x = texCoord[0];
				vertices[count].uv.y = texCoord[1];
			}
		}

	}

	//メッシュを作成
	_modelData
		.emplace("Test", new Mesh(vertices, indices));

}

FBXLoader::~FBXLoader() {

	for (auto item : _meshes) {
		if (item) item->Destroy();
	}

	for (auto item : _modelData) {
		if (item.second) delete item.second;
	}

	if (_scene) _scene->Destroy();
	if (_manager) _manager->Destroy();

}

