#include "Primitive.h"

const vector<Vertex> Primitive::polygon = vector<Vertex>{
	{ { -0.5f, -0.5f,  0.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 1.0f } },
	{ { -0.5f,  0.5f,  0.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 0.0f, 0.0f } },
	{ {  0.5f, -0.5f,  0.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 1.0f } },
	{ {  0.5f,  0.5f,  0.0f },{ 0.0f, 1.0f, 1.0f, 1.0f },{ 1.0f, 0.0f } },
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

const vector<Vertex> Primitive::GetPrimitiveVertex(PrimitiveType type) {

	vector<Vertex> v;

	switch (type) {
		case PrimitiveType::Polygon:
			copy(polygon.begin(), polygon.end(), back_inserter(v));
			break;
		case PrimitiveType::Star:
			copy(star.begin(), star.end(), back_inserter(v));
			break;
		default:
			break;
	}

	return v;
}