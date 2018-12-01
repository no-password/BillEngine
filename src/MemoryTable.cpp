#include "MemoryTable.h"

#include <memory>
#include <iostream>

MemoryTable* instance_MemoryTable = nullptr;

MemoryTable::MemoryTable() {
	this->totalSize = 0;
}

/**
 * MemoryTable.put is called when a memory object is being constructed, 
 * thus the polymorphic behaviour of getSize() will not occur, so we need to pass 
 * the size in.
 */
void MemoryTable::put(MemoryObject* memObject, size_t size) {
	/* why map.insert({key, val}) instead of map.insert(key, val)? */
	memoryMap.insert(std::make_pair(memObject, size));
	totalSize += size;
}

void MemoryTable::update(MemoryObject *memObject) {
	if (memoryMap.find(memObject) == memoryMap.end()) {
		return;
	}

	totalSize -= (memoryMap.find(memObject))->second;
	memoryMap.insert_or_assign(memObject, memObject->getSize());
	totalSize += memObject->getSize();
}

void MemoryTable::remove(MemoryObject* memObject) {
	auto keyValue = memoryMap.find(memObject);
	if (keyValue == memoryMap.end()) {
		return;
	}

	totalSize -= keyValue->second;
	memoryMap.erase(memObject);
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
	stream << totalSize << " bytes" << std::endl;
	for (auto iter = memoryMap.begin(); iter != memoryMap.end(); ++iter) {
		MemoryObject* memObject = iter->first;
		stream << memObject << "\t" << memObject->getSize() << " bytes" << std::endl;
	}
}
