#include "StaticRenderableObject.h"


StaticRenderableObject::StaticRenderableObject(const std::string filePath, const Point3D* position)
:VertexFormattedObject(filePath, SRO_FILE_FORMAT) {
	globalPosition.x = position->x;
	globalPosition.y = position->y;
	globalPosition.z = position->z;
}

StaticRenderableObject::~StaticRenderableObject() {
	
}

const Point3D* StaticRenderableObject::getGlobalPosition() {
	return &globalPosition;
}
