#include "VertexFormattedObject.h"
#include "test_common.h"
#include "BillEngine.h"
#include "Geometry.h"
#include "BufferCollection.h"
#include "MatrixCollection.h"
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
		stream << vertices[i] << "\t";
		if (((i + 1) % 3) == 0) {
			stream << std::endl;
		}
	}

	stream << "FACES: " << numFaces << std::endl;
	for (size_t i = 0; i < numFaces; i++) {
		stream << faces[i] << "\t";
		if (((i + 1) % pointsPerFace) == 0) {
			stream << std::endl;
		}
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
