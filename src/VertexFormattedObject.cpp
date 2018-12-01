#include "VertexFormattedObject.h"
#include <iostream>
#include <fstream>
#include <cassert>

#define HEADER_OFF "OFF"

#define STR_TOKEN " "

size_t VertexFormattedObject::getSize() const {
	return sizeof(VertexFormattedObject) + numFaces * sizeof(Face) + numVertices * sizeof(Point3D);
}

VertexFormattedObject::VertexFormattedObject(std::string filePath, VERTEX_FILE_FORMAT format) 
:MemoryObject(this->getSize()){
	numFaces = 0;
	numVertices = 0;
	faces = nullptr;
	vertices = nullptr;

	switch (format) {
		case OFF:
			readOFF(filePath);
			break;
	}
}

VertexFormattedObject::~VertexFormattedObject() {
	if (vertices != nullptr) {
		delete vertices;
	}

	if (faces != nullptr) {
		delete faces;
	}

	std::cout << "Deleted faces/verts" << std::endl;
}

void VertexFormattedObject::readOFF(std::string filePath) {
	std::string line;
	std::ifstream file(filePath, std::ifstream::in);
	if (!file.is_open()) {
		std::cout << "Could not open '" << filePath << "'" << std::endl;
		return;
	}

	/* Verfiy OFF heaer */
	if (!getline(file, line) || line != HEADER_OFF) {
		std::cout << "File is improporly formatted (does not have OFF header)" << std::endl;
		file.close();
		return;
	}

	/* Find the line which specefies vertex/face/edge count */
	while(getline(file, line)) {
		if (line.at(0) == '#') {
			continue;
		}

		if (checkLineForVertexCounts(line)) {
			break;
		}
	}

	vertices = new Point3D[numVertices];
	faces = new Face[numFaces];

	/* read vertices from OFF file */
	size_t i = 0;
	while (i < numVertices) {
		if (!getline(file, line)) {
			std::cout << "Improperly formatted OFF file" << std::endl;
			delete vertices;
			vertices = nullptr;
			delete faces;
			faces = nullptr;
		}
		if (checkLineForVertex(line, i)) {
			i++;
		}
	}

	i = 0;
	while (i < numFaces) {
		if (!getline(file, line)) {
			std::cout << "Improperly formatted  OFF file [2]" << std::endl;
			delete vertices;
			vertices = nullptr;
			delete faces;
			faces = nullptr;
		}
		if (checkLineForFace(line, i)) {
			i++;
		}
	}

	MemoryObject::updateSize();
}

bool VertexFormattedObject::checkLineForVertexCounts(std::string line) {
	if (lineIsCommentOrEmpty(line)) {
		return false;
	}

	std::vector<std::string> tokens = tokenize(line, STR_TOKEN);
	if (tokens.size() >= 3) {
		if (stringIsInteger(tokens[0]) && stringIsInteger(tokens[1]) && stringIsInteger(tokens[2])) {
			numVertices = stoi(tokens[0]);
			numFaces = stoi(tokens[1]);
			numEdges = stoi(tokens[2]);
			return true;
		} 
	}

	return false;
}

bool VertexFormattedObject::checkLineForVertex(std::string line, const size_t verticesIndex) {

	std::vector<std::string> tokens = tokenize(line, STR_TOKEN);
	if (tokens.size() < 3) {
		return false;
	}

	if (stringIsNumber(tokens[0]) && stringIsNumber(tokens[1]) && stringIsNumber(tokens[2])) {
		vertices[verticesIndex].x = stof(tokens[0]);
		vertices[verticesIndex].y = stof(tokens[1]);
		vertices[verticesIndex].z = stof(tokens[2]);

		return true;
	}

	return false;
}

bool areTokensIntegers(const std::vector<std::string>* tokens, int_u8 start, int_u8 end);
bool VertexFormattedObject::checkLineForFace(std::string line, const size_t facesIndex) {
	if (lineIsCommentOrEmpty(line)) {
		return false;
	}

	std::vector<std::string> tokens = tokenize(line, STR_TOKEN);
	if (!stringIsInteger(tokens[0])) {
		return false;
	}

	int_u8 numPoints = stoi(line);
	if (tokens.size() - 1 < numPoints) {
		return false;
	}

	if (!areTokensIntegers(&tokens, 1, numPoints+1)) {
		return false;
	}

	faces[facesIndex].numPoints = numPoints;
	faces[facesIndex].pointIndices = new int[numPoints];
	for (int_u8 i = 0; i < numPoints; i++) {
		(faces[facesIndex].pointIndices)[i] = stoi(tokens[i+1]);
	}

	/* Check if a color is specefied */
	if (tokens.size() - (numPoints+1) >= 3) {
		if (areTokensIntegers(&tokens, numPoints+1, numPoints+4)) {
			faces[facesIndex].color = new Color();
			faces[facesIndex].color->R = stoi(tokens[numPoints+1]);
			faces[facesIndex].color->G = stoi(tokens[numPoints+2]);
			faces[facesIndex].color->B = stoi(tokens[numPoints+3]);
		}
	}

	return true;
}

bool areTokensIntegers(const std::vector<std::string>* tokens, int_u8 start, int_u8 end) {
	assert(start < end);
	assert(start < tokens->size());
	assert(end <= tokens->size());
	for (int_u8 i = start; i < end; i++) {
		if (!stringIsInteger((*tokens)[i])) {
			return false;
		}
	}

	return true;
}

bool VertexFormattedObject::lineIsCommentOrEmpty(std::string line) {
	if (line.length() == 0) {
		return true;
	}

	if (line.at(0) == '#') {
		return true;
	}

	return false;
}
