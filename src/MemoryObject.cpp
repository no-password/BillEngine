#include "MemoryObject.h"
#include "BillEngine.h"

MemoryObject::MemoryObject(size_t size) {
	BillEngine::addMemoryObject(this, size);
}

MemoryObject::~MemoryObject() {
	BillEngine::removeMemoryObject(this);
}
/*
size_t MemoryObject::getSize() const {
	return sizeof(MemoryObject);
}*/

std::ostream& operator<<(std::ostream& os, const MemoryObject& m) {
    os << &m << " -> \t" << m.getSize() << "bytes";
    return os;
}


std::ostream& operator<<(std::ostream& os, const MemoryObject* m) {
    os << m << " -> \t" << m->getSize() << "bytes";
    return os;
}
