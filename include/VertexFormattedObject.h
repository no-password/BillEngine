#ifndef VERTEX_FORMATTED_OBJECT_H
#define VERTEX_FORMATTED_OBJECT_H

#include "common.h"
#include "MemoryObject.h"
#include "Geometry.h"
#include "MatrixCollection.h"
#include "BufferCollection.h"

#define VERTEX_FILE_FORMAT int_u8
#define OFF 0

class VertexFormattedObject: public MemoryObject {
	private:
		void readOFF(std::string filePath);
		bool checkLineForVertexCounts(std::string line);
		bool checkLineForVertex(std::string line, const size_t verticesIndex);
		bool checkLineForFace(std::string line, const size_t facesIndex);
		bool lineIsCommentOrEmpty(std::string line);
		void transformOFFData();
		
		size_t numFileVertices;
		size_t numFileFaces;
		size_t numEdges;
		Point3D* fileVertices;
		Face* fileFaces;
	public:
		GLfloat* vertices;
		size_t numVertices;
		int* faces;
		GLfloat* colors;
		int_u8 pointsPerFace;
		size_t numFaces;
		
		size_t getSize() const;
		void render(BufferCollection* bufs, MatrixCollection* mats);
		VertexFormattedObject(const std::string filePath, VERTEX_FILE_FORMAT format);
		virtual ~VertexFormattedObject();
};

#endif
