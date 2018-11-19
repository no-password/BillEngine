#ifndef MEM_TABLE_H
#define MEM_TABLE_H

#include "common.h"
#include "BillEngine.h"

#include <set>

/* Keeps track of total memory used by MemoryObjects, does not free/alloc memory for MemoryObjects */
class MemoryTable {
	private:
		MemoryTable();
		std::set<MemoryObject*> memorySet;
		unsigned long totalSize;

		void put(MemoryObject* memObject);
		void remove(MemoryObject* memObject);

		friend BillEngine;
	public:
		MemoryTable* getInstance();
		unsigned long getTotalSize();
		void dump(std::ostream& stream);
};

#endif
