#ifndef VERTEX_FORMATTED_OBJECT_H
#define VERTEX_FORMATTED_OBJECT_H

#include "common.h"
#include "MemoryObject.h"
#include "Geometry.h"

#define VERTEX_FILE_FORMAT int_u8
#define OFF 0

class VertexFormattedObject: public MemoryObject {
	private:
		void readOFF(std::string filePath);
		bool checkLineForVertexCounts(std::string line);
		bool checkLineForVertex(std::string line, const size_t verticesIndex);
		bool checkLineForFace(std::string line, const size_t facesIndex);
		bool lineIsCommentOrEmpty(std::string line);
	protected:
		size_t numVertices;
		size_t numFaces;
		size_t numEdges;
		Point3D* vertices;
		Face* faces;
		
		VertexFormattedObject(const std::string filePath, VERTEX_FILE_FORMAT format);
		virtual ~VertexFormattedObject();
	public:
		size_t getSize() const;
};

#endif
