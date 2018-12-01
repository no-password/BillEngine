#ifndef MEM_OBJ_H
#define MEM_OBJ_H

#include <cstddef>
#include <ostream>

/**
 * Represents resoure in memory used by BillEngine. This could be, for example, windows, objects, entities, etc. Is abstract class. Its job is to tell the memory tacking table in the engine how many resources are used an by what. 
 *
 * When inhereiting from this class, super class contrustor must be called explicity:
 * <code>
 * 	Foo::Foo()
 * 	MemoryObject(this->getSize()) {
 *		...
 * 	}
 * </code>
 */
class MemoryObject {
	protected:
		MemoryObject(size_t size);
		void updateSize();
	public:
		virtual ~MemoryObject();
		virtual size_t getSize() const = 0;
};

#endif
