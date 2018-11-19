#include "MemoryObject.h"

std::ostream& operator<<(std::ostream& os, const MemoryObject& m) {
    os << &m << " -> \t" << m.getSize() << "bytes";
    return os;
}


std::ostream& operator<<(std::ostream& os, const MemoryObject* m) {
    os << m << " -> \t" << m->getSize() << "bytes";
    return os;
}
