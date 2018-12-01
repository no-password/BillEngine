#include "VertexFormattedObject.h"
#include "test_common.h"
#include "BillEngine.h"
#include "Geometry.h"
#include <iostream>
#include <ostream>

#define OFF_FILE_PATH "tst_res/cube.off"

class Foo: public VertexFormattedObject {
	public:
		Foo(const std::string filePath);
		~Foo();
		size_t getSize() const;
		void dump(std::ostream& stream);
};

Foo::Foo(const std::string filePath) 
:VertexFormattedObject(filePath, OFF) {
	
}

Foo::~Foo() {

}

size_t Foo::getSize() const {
	return sizeof(Foo) + VertexFormattedObject::getSize();
}

void Foo::dump(std::ostream& stream) {
	stream << "VERTICES: " << numVertices << std::endl;
	for (size_t i = 0; i < numVertices; i++) {
		Point3D* point = &(vertices[i]);
		stream << point->x << "\t" << point->y << "\t" << point->z <<  std::endl;
		//TODO: override << for Point3D/Point2D
	}

	stream << "FACES: " << numFaces << std::endl;
	for (size_t i = 0; i < numFaces; i++) {
		Face* face = &(faces[i]);
		stream << (int) faces->numPoints << ": ";
		for (int_u8 i = 0; i < faces->numPoints; i++) {
			stream << face->pointIndices[i] << " ";
		}

		if (face->color != nullptr) {
			stream << " | "<< face->color->R << " ";
			stream << face->color->G << " "; 
			stream << face->color->B;
		}

		stream << std::endl;
	}
}

Foo* foo = nullptr;
MemoryTable* memTable = nullptr;

static void before() {
	if (BillEngine::init() != 0) {
		std::cout << "Failed to init engine" << std::endl;
		exit(EXIT_FAILURE);
	}

	memTable = MemoryTable::getInstance();
}

static void initTest() {
	std::cout << _FNAME_ << std::endl;
	foo = new Foo(OFF_FILE_PATH);
	assert(foo != nullptr);
	memTable->dump(std::cout);
	foo->dump(std::cout);
}

int main(int argc, char** argv) {
	before();
	initTest();
}
