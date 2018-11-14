#include "Primitive.h"
#include "Mesh.h"

const vector<Mesh*> Primitive::meshData = {
	//polygon
	new Mesh(
		vector<Vertex> {
			{ { -0.5f, -0.5f,  0.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },
			{ { -0.5f,  0.5f,  0.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
			{ {  0.5f, -0.5f,  0.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
			{ {  0.5f,  0.5f,  0.0f},{ 1.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f } },
		},
		vector<int> {
			{0, 1, 2, 3, 2, 0}
		})
	//star
	//new Mesh(),
};

const vector<Vertex> Primitive::polygon = vector<Vertex>{
	{ { -0.5f, -0.5f,  0.0f},{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },
	{ { -0.5f,  0.5f,  0.0f},{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.5f, -0.5f,  0.0f},{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.0f},{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f } },
};

const vector<Vertex> Primitive::star = vector<Vertex>{
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//1
	{ { -0.6f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.3f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.9f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//1end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//2
	{ {  0.3f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.3f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  1.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//2end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//3
	{ {  0.3f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.6f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.9f,  0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//3end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//4
	{ {  0.3f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.6f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.9f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//4end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//5
	{ {  0.3f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.3f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f, -1.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//5end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//6
	{ { -0.6f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.3f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ { -0.9f, -0.5f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },//6end
	{ {  0.0f,  0.0f,  0.0f },{ 1.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
};

Primitive::Primitive() {}
Primitive::~Primitive() {}

Mesh* Primitive::GetPrimitiveMesh(PrimitiveType type) {

	//vector<Vertex> v;

	return new Mesh(*meshData[int(PrimitiveType::Polygon)]);

	//switch (type) {
	//	case PrimitiveType::Polygon:
	//		return new meshData;
	//		break;
	//	case PrimitiveType::Star:
	//		copy(star.begin(), star.end(), back_inserter(v));
	//		break;
	//	default:
	//		break;
	//}

	//return v;
}
