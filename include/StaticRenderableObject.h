#ifndef STATIC_RENDERABLE_OBJECT_H
#define STATIC_RENDERABLE_OBJECT_H

#include "common.h"
#include "VertexFormattedObject.h"

#define SRO_FILE_FORMAT OFF

class StaticRenderableObject: public VertexFormattedObject {
	private:
		Point3D globalPosition;
	public:
		StaticRenderableObject(const std::string filePath, const Point3D* position);
		~StaticRenderableObject();
		const Point3D* getGlobalPosition();
};

#endif
