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

	//���W����ϊ�
	FbxAxisSystem::DirectX.ConvertScene(_scene);

	FbxGeometryConverter fgc(_manager);
	fgc.Triangulate(_scene, true);

	auto meshCount = _scene->GetSrcObjectCount<FbxMesh>();
	//���b�V���̐������J��Ԃ�
	for (auto i = 0; i < meshCount; ++i) {
		//���b�V���f�[�^���擾
		auto mesh = _scene->GetSrcObject<FbxMesh>(i);

		_meshes.push_back(mesh);
	}

	auto vertices = vector<Vertex>();
	auto indices = vector<int>();

	for (auto mesh : _meshes) {
		int polygonCount = mesh->GetPolygonCount();

		vector<int> indexList;

		//�C���f�b�N�X�f�[�^�̐ݒ�
		auto vertexOffset = vertices.size();
		for (auto i = 0; i < polygonCount; ++i) {
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 0));
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 1));
			indexList.push_back(vertexOffset + mesh->GetPolygonVertex(i, 2));
		}
		//indices�̌��ɒǉ�
		copy(indexList.begin(), indexList.end(), back_inserter(indices));

		//UV���擾
		//���_�Ɋi�[����Ă���SUV�Z�b�g�𖼑O�Ŏ擾
		FbxStringList uvsetName;
		mesh->GetUVSetNames(uvsetName);

		//uvsets�ɁA���_���Ƃ�UV���i�[���Ă����
		FbxArray<FbxVector2> uvsets;
		mesh->GetPolygonVertexUVs(uvsetName.GetStringAt(0), uvsets);

		//�@�����擾
		FbxArray<FbxVector4> normals;
		mesh->GetPolygonVertexNormals(normals);

		//���_�f�[�^�̐ݒ�
		int vertexCount = mesh->GetControlPointsCount();
		for (auto i = 0; i < vertexCount; ++i) {
			
			//���W
			auto cp = mesh->GetControlPointAt(i);

			Vertex v;
			v.pos.x = cp[0];
			v.pos.y = cp[1];
			v.pos.z = cp[2];
			v.pos.w = 1.0f;

			//���_�J���[
			v.col = { 1.0f, 1.0f, 1.0f, 1.0f };

			//UV
			auto uv = uvsets.GetAt(i);
			v.uv.x = uv[0];
			v.uv.y = 1.0 - uv[1];

			//�@��
			auto normal = normals.GetAt(i);
			v.normal.x = normal[0];
			v.normal.y = normal[1];
			v.normal.z = normal[2];

			vertices.push_back(v);

		}
	}

	//���b�V�����쐬
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

