#ifndef MATRIX_COLLECTION_H
#define MATRIX_COLLECTION_H

typedef struct matrixCollection {
	GLfloat transform[16], view[16], projection[16]; //transform/view/projection matrices
} MatrixCollection;

#endif
