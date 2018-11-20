#include "MemoryObject.h"
#include "BillEngine.h"

MemoryObject::MemoryObject() {
	BillEngine::addMemoryObject(this);
}

MemoryObject::~MemoryObject() {
	BillEngine::removeMemoryObject(this);
}

size_t MemoryObject::getSize() const {
	return sizeof(MemoryObject);
}

std::ostream& operator<<(std::ostream& os, const MemoryObject& m) {
    os << &m << " -> \t" << m.getSize() << "bytes";
    return os;
}


std::ostream& operator<<(std::ostream& os, const MemoryObject* m) {
    os << m << " -> \t" << m->getSize() << "bytes";
    return os;
}
