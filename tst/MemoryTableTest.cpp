#include "test_common.h"

#include "MemoryTable.h"
#include "MemoryObject.h"
#include "BillEngine.h"

#include <iostream>
#include <cassert>

struct Bar {
	int a;
	float b;
};

class Foo: public MemoryObject {
	public:
		struct Bar* bar;
		int baz;
		
		Foo();
		~Foo();
		size_t getSize() const;
};

Foo::Foo() 
:MemoryObject(this->getSize()){
	bar = new struct Bar;
	bar->a = 10;
	bar->b = 3.14f;
	baz = 4;
}

Foo::~Foo() {
	delete bar;
}

size_t Foo::getSize() const {
	return sizeof(Foo) + sizeof(struct Bar);
}

Foo* foo1;
Foo* foo2;

static void before() {
	if (BillEngine::init() != 0) {
		std::cout << "Failed to init BillEngine!" << std::endl;
	}

	foo1 = nullptr;
	foo2 = nullptr;
}

static void putTest() {
	std::cout << "[" << _FNAME_ << "]" << std::endl;
	MemoryTable* table = MemoryTable::getInstance();
	assert(table != NULL);
	foo1 = new Foo();
	foo2 = new Foo();

	const size_t EXPECTED_SIZE = 2 * (sizeof(Foo) + sizeof(struct Bar));

	table->dump(std::cout);
	assert(table->getTotalSize() == EXPECTED_SIZE);
}

static void removeTest() {
	std::cout << "[" << _FNAME_ << "]" << std::endl;
	MemoryTable* table = MemoryTable::getInstance();
	assert(table != NULL);
	delete foo1;
	delete foo2;

	table->dump(std::cout);
	assert(table->getTotalSize() == 0);
}

int main(int argc, char** argv) {
	std::cout << "START: " << argv[0] << std::endl;
	before();
	putTest();
	removeTest();
	std::cout << "FINISHED: " << argv[0] << std::endl;
}
