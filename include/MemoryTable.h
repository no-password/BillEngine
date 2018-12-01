#ifndef MEM_TABLE_H
#define MEM_TABLE_H

#include "BillEngine.h"

#include <unordered_map>

class BillEngine;
/* honestly, fuck this shitty language */

/* Keeps track of total memory used by MemoryObjects, does not free/alloc memory for MemoryObjects */
class MemoryTable {
	private:
		MemoryTable();
		std::unordered_map<MemoryObject*, size_t> memoryMap;
		unsigned long totalSize;

		void put(MemoryObject* memObject, size_t size);
		void update(MemoryObject *memObject);
		void remove(MemoryObject* memObject);

		friend BillEngine;
	public:
		static MemoryTable* getInstance();
		unsigned long getTotalSize();
		void dump(std::ostream& stream);
};

#endif
