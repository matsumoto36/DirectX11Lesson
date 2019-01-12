#include "FBXLoader.h"



FBXLoader::FBXLoader() :
	_manager(FbxManager::Create()),
	_scene(FbxScene::Create(_manager, "")) {
	
	FbxString fileName = "Resources/Model/nojya.FBX";

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
		int polygonCount = mesh->GetPolygonCount();

		vector<int> indexList;

		//インデックスデータの設定
		auto vertexOffset = vertices.size();
		for (auto i = 0; i < polygonCount; ++i) {
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 0));
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 1));
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 2));
		}
		//indicesの後ろに追加
		copy(indexList.begin(), indexList.end(), back_inserter(indices));

		//UVを取得
		//頂点に格納されている全UVセットを名前で取得
		FbxStringList uvsetName;
		mesh->GetUVSetNames(uvsetName);

		//uvsetsに、頂点ごとのUVを格納してくれる
		FbxArray<FbxVector2> uvsets;
		mesh->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

		//法線を取得
		FbxArray<FbxVector4> normals;
		mesh->GetPolygonVertexNormals(normals);

		//頂点データの設定
		int vertexCount = mesh->GetControlPointsCount();
		for (auto i = 0; i < vertexCount; ++i) {
			
			//座標
			auto cp = mesh->GetControlPointAt(i);

			Vertex v;
			v.pos.x = cp[0];
			v.pos.y = cp[1];
			v.pos.z = cp[2];
			v.pos.w = 1.0f;

			//頂点カラー
			v.col = { 1.0f, 1.0f, 1.0f, 1.0f };

			//UV
			auto uv = uvsets.GetAt(i);
			v.uv.x = uv[0];
			v.uv.y = 1.0 - uv[1];

			//法線
			auto normal = normals.GetAt(i);
			v.normal.x = normal[0];
			v.normal.y = normal[1];
			v.normal.z = normal[2];

			vertices.push_back(v);

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

