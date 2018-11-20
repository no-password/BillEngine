#include "MemoryTable.h"

#include <memory>

MemoryTable* instance_MemoryTable = nullptr;

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
	if (instance_MemoryTable == nullptr) {
		instance_MemoryTable = new MemoryTable();
	}

	return instance_MemoryTable;
}

unsigned long MemoryTable::getTotalSize() {
	return totalSize;
}

void MemoryTable::dump(std::ostream& stream) {
	stream << memorySet.size() << " bytes" << std::endl;
	for (MemoryObject* memObject: memorySet) {
		stream << memObject << "\t" << memObject->getSize() << " bytes" << std::endl;
	}
}
