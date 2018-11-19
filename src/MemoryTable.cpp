#include "MemoryTable.h"

#include <memory>

MemoryTable* instance = nullptr;

MemoryTable::MemoryTable() {
	this->totalSize = 0;
}

void MemoryTable::put(MemoryObject* memObject) {
	memorySet.insert(memObject);
	totalSize += memObject->getSize();
}

void MemoryTable::remove(MemoryObject* memObject) {
	memorySet.erase(memObject);
	totalSize -= memObject->getSize();
}

MemoryTable* MemoryTable::getInstance() {
	if (instance == nullptr) {
		instance = new MemoryTable();
	}

	return instance;
}

unsigned long MemoryTable::getTotalSize() {
	return totalSize;
}

void MemoryTable::dump(std::ostream& stream) {
	for (MemoryObject* memObject: memorySet) {
		stream << memObject << std::endl;
	}
}
