#ifndef BUFFER_COLLECCTION_H
#define BUFFER_COLLECCTION_H

#include "common.h"

/* Must be declared globally in main() */
typedef struct bufferCollection {
	GLuint vao, vbo[2], ebo, pos, color, //vertex buffer identifiers
		   program,                      //shader program identifier
		   Modelview, Projection;        //Modelview/Projection identifiers
} BufferCollection;

#endif
