#ifndef MEM_OBJ_H
#define MEM_OBJ_H

#include <cstddef>
#include <ostream>

class MemoryObject {
	public:
		virtual ~MemoryObject() {};
		virtual size_t getSize() const;
};

#endif
