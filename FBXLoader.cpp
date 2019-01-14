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

		auto polygonCount = mesh->GetPolygonCount();

		//�|���S������
		for (auto i = 0; i < polygonCount; ++i) {
			for (auto j = 0; j < 3; j++) {

				//�C���f�b�N�X�f�[�^
				auto index = mesh->GetPolygonVertex(i, j);
				indices.push_back(index);

				Vertex v;

				//���W
				auto pos = mesh->GetControlPointAt(index);
				v.pos.x = pos[0];
				v.pos.y = pos[1];
				v.pos.z = pos[2];
				v.pos.w = 1.0f;

				//���_�J���[
				v.col = { 1.0f, 1.0f, 1.0f, 1.0f };

				//�@��
				FbxVector4 normal;
				mesh->GetPolygonVertexNormal(i, j, normal);
				v.normal.x = normal[0];
				v.normal.y = normal[1];
				v.normal.z = normal[2];

				vertices.push_back(v);
			}
		}


		//UV���擾
		//���_�Ɋi�[����Ă���SUV�Z�b�g�𖼑O�Ŏ擾
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

