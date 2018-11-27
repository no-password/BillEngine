#include "MemoryTable.h"

#include <memory>

MemoryTable* instance_MemoryTable = nullptr;

MemoryTable::MemoryTable() {
	this->totalSize = 0;
}

void MemoryTable::put(MemoryObject* memObject, size_t size) {
	memorySet.insert(memObject);
	totalSize += size;
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
	size_t total = 0;
	for (MemoryObject* memObject: memorySet) {
		stream << memObject << "\t" << memObject->getSize() << " bytes" << std::endl;
		total += memObject->getSize();
	}
	stream << total << " bytes" << std::endl;
	totalSize = total;
}
