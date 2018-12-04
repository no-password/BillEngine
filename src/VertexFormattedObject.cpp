#include "VertexFormattedObject.h"
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cassert>

#define HEADER_OFF "OFF"

#define STR_TOKEN " "

#define toRGB( x ) 255.0f / x

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

	if (colors != nullptr) {
		delete colors;
	}

	std::cout << "Deleted faces/verts" << std::endl;
}

void VertexFormattedObject::render(BufferCollection* bufs, MatrixCollection* mats) {
    /* initialize vbo/vao/ebo */
    glGenBuffers(2, bufs->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, (bufs->vbo)[0]);
    glBufferData(GL_ARRAY_BUFFER, numVertices, vertices, GL_STATIC_DRAW);


    glBindBuffer(GL_ARRAY_BUFFER, (bufs->vbo)[1]);
    glBufferData(GL_ARRAY_BUFFER, numVertices, colors, GL_STATIC_DRAW);


    glGenBuffers(1, &(bufs->ebo));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufs->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numFaces, faces, GL_STATIC_DRAW);


    glGenVertexArrays(1, &(bufs->vao));
    glBindVertexArray(bufs->vao);


    bufs->pos = glGetAttribLocation(bufs->program, "vPos");
    glEnableVertexAttribArray(bufs->pos);
    glBindBuffer(GL_ARRAY_BUFFER, (bufs->vbo)[0]);
    glVertexAttribPointer(bufs->pos, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    bufs->color = glGetAttribLocation(bufs->program, "vColor");
    glEnableVertexAttribArray(bufs->color);
    glBindBuffer(GL_ARRAY_BUFFER, (bufs->vbo)[1]);
    glVertexAttribPointer(bufs->color, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glDrawElements(GL_TRIANGLES, pointsPerFace, GL_UNSIGNED_INT, (void *)0);
}

void printFileContents(Point3D* points, size_t numPoints, Face* faces, size_t numFaces);
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

	fileVertices = new Point3D[numFileVertices];
	fileFaces = new Face[numFileFaces];

	/* read vertices from OFF file */
	size_t i = 0;
	while (i < numFileVertices) {
		if (!getline(file, line)) {
			std::cout << "Improperly formatted OFF file" << std::endl;
			delete fileVertices;
			fileVertices = nullptr;
			delete fileFaces;
			fileFaces = nullptr;
		}
		if (checkLineForVertex(line, i)) {
			i++;
		}
	}

	i = 0;
	while (i < numFileFaces) {
		if (!getline(file, line)) {
			std::cout << "Improperly formatted  OFF file [2]" << std::endl;
			delete fileVertices;
			fileVertices = nullptr;
			delete fileFaces;
			fileFaces = nullptr;
		}
		if (checkLineForFace(line, i)) {
			i++;
		}
	}

	file.close();
	printFileContents(fileVertices, numFileVertices, fileFaces, numFileFaces);

	transformOFFData();

	MemoryObject::updateSize();
}

bool VertexFormattedObject::checkLineForVertexCounts(std::string line) {
	if (lineIsCommentOrEmpty(line)) {
		return false;
	}

	std::vector<std::string> tokens = tokenize(line, STR_TOKEN);
	if (tokens.size() >= 3) {
		if (stringIsInteger(tokens[0]) && stringIsInteger(tokens[1]) && stringIsInteger(tokens[2])) {
			numFileVertices = stoi(tokens[0]);
			numFileFaces = stoi(tokens[1]);
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
		fileVertices[verticesIndex].x = stof(tokens[0]);
		fileVertices[verticesIndex].y = stof(tokens[1]);
		fileVertices[verticesIndex].z = stof(tokens[2]);

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

	fileFaces[facesIndex].numPoints = numPoints;
	pointsPerFace = numPoints;
	fileFaces[facesIndex].pointIndices = new int[numPoints];
	for (int_u8 i = 0; i < numPoints; i++) {
		(fileFaces[facesIndex].pointIndices)[i] = stoi(tokens[i+1]);
	}

	/* Check if a color is specefied */
	if (tokens.size() - (numPoints+1) >= 3) {
		if (areTokensIntegers(&tokens, numPoints+1, numPoints+4)) {
			fileFaces[facesIndex].color = new Color();
			fileFaces[facesIndex].color->R = stoi(tokens[numPoints+1]);
			fileFaces[facesIndex].color->G = stoi(tokens[numPoints+2]);
			fileFaces[facesIndex].color->B = stoi(tokens[numPoints+3]);
		}
	}

	return true;
}

void VertexFormattedObject::transformOFFData() {
	std::unordered_map<std::string, std::unordered_map<int, int>> colorToIndexMap;
	std::vector<float> newVertices;
	std::vector<int> newFaces;
	std::vector<float> newColors;
	size_t newVerticesIndex = 0;

	for (size_t i = 0; i < numFileFaces; i++) {
		Face* face = &(fileFaces[i]);
		Color* color = face->color;

		for (int_u8 j = 0; j < face->numPoints; j++) {
			int index = (face->pointIndices)[j];
			auto keyValuePair = colorToIndexMap.find(color->getUniqueString());

			if (keyValuePair != colorToIndexMap.end()) {
				std::unordered_map<int, int>* oldToNewIndexMap = &(colorToIndexMap[color->getUniqueString()]);//keyValuePair->second;
				auto indexKeyValuePair = oldToNewIndexMap->find(index);
				if (indexKeyValuePair != oldToNewIndexMap->end()) {
					newFaces.push_back(indexKeyValuePair->second);
				} else {
					newVertices.push_back((fileVertices[index]).x);
					newVertices.push_back((fileVertices[index]).y);
					newVertices.push_back((fileVertices[index]).z);
					std::cout << "New vertex for color " << color->getUniqueString() << " -> ";
					std::cout << (fileVertices[index]).x << "," << (fileVertices[index]).y << "," << (fileVertices[index]).z << std::endl;
					newColors.push_back(toRGB(color->R));
					newColors.push_back(toRGB(color->G));
					newColors.push_back(toRGB(color->B));
					newFaces.push_back(newVerticesIndex);
					oldToNewIndexMap->insert({index, newVerticesIndex++});
				}
			} else {
				newFaces.push_back(newVerticesIndex);
				colorToIndexMap[color->getUniqueString()][index] = newVerticesIndex++;
			}
		}
	}

	delete fileVertices;
	delete fileFaces;
	numVertices = newVertices.size();
	numFaces = newFaces.size();
	vertices = new GLfloat[numVertices];
	colors = new GLfloat[numVertices];
	faces = new int[numFaces];
	
	std::copy(newVertices.begin(), newVertices.end(), vertices);
	std::copy(newColors.begin(), newColors.end(), colors);
	std::copy(newFaces.begin(), newFaces.end(), faces);
/*
	std::unordered_map<std::string, std::vector<Face*>> colorToFaceMap;
	for (size_t i = 0; i < numFileFaces; i++) {
		Face* face = &(fileFaces[i]);
		if (face->color != nullptr) {
			Color* color = face->color;
			std::string colorCode = color->getUniqueString();
			auto entry = colorToFaceMap.find(colorCode);
			if (entry != colorToFaceMap.end()) {
				(entry->second).push_back(face);
			} else {
				colorToFaceMap[colorCode].push_back(face);
			}
		}
	}

	for (auto iter = colorToFaceMap::iterator; iter != colorToFaceMap.end(); ++iter) {
		for (auto faceIter = (iter->second).begin(); faceIter != (iter->second).end(); ++faceIter) {
			Face* face = *faceIter;
			for (int_u8 i = 0; i < face->numPoints; i++) {
				newVertices.push_back()
			}
		}
	}*/
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

void printFileContents(Point3D* points, size_t numPoints, Face* faces, size_t numFaces) {
	for (size_t i = 0; i < numPoints; i++) {
		std::cout << (points[i]).x << "\t";
		std::cout << (points[i]).y << "\t";
		std::cout << (points[i]).z << "\t";
		std::cout << std::endl;
	}

	for (size_t i = 0; i < numFaces; i++) {
		for (size_t j = 0; j < (faces[i]).numPoints; j++) {
			std::cout << (faces[i]).pointIndices[j] << "\t";
		}

		std::cout << std::endl;
	}
}
