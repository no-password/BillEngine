#ifndef MEM_TABLE_H
#define MEM_TABLE_H

#include "BillEngine.h"

#include <set>

class BillEngine;
/* honestly, fuck this shitty language */

/* Keeps track of total memory used by MemoryObjects, does not free/alloc memory for MemoryObjects */
class MemoryTable {
	private:
		MemoryTable();
		std::set<MemoryObject*> memorySet;
		unsigned long totalSize;

		void put(MemoryObject* memObject, size_t size);
		void remove(MemoryObject* memObject);

		friend BillEngine;
	public:
		static MemoryTable* getInstance();
		unsigned long getTotalSize();
		void dump(std::ostream& stream);
};

#endif
