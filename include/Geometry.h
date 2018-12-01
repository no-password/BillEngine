#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "common.h"
#include "Color.h"
#include <cmath>

#define d2r(angleDegrees) (angleDegrees * M_PI / 180.0)

typedef enum axis {AXIS_X, AXIS_Y, AXIS_Z} Axis;

typedef struct point3d {
	GLfloat x, y, z;
} Point3D;

/**
 * Computer the scalar distance between two 3D points
 */
GLfloat distance(const Point3D* p, const Point3D* q);

/**
 * Output summary of Point3D struct to std::cout
 */
void printPoint(const Point3D p);

/**
 * Rotates a target point about a fixed point one on an axis.
 * For example, if given AXIS_Y, this function will rotate target along the 
 * X-Z plane, about the Y dimension of fixed
 * @param fixed Rotate about this
 * @param target rotate this
 * @param theta angle at which to rotate
 * @param axis rotate about which axis
 */
void rotate(const Point3D* fixed, Point3D* target, double theta, Axis axis);


typedef struct point2d {
	GLfloat x, y;
} Point2D;

GLfloat distance(const Point2D* p, const Point2D* q);

/**
 * Face
 */
typedef struct face {
	int_u8 numPoints; 
	int* pointIndices;
	Color* color = nullptr;
} Face;

void destroyFace(Face* face);
#endif
