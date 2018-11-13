#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "common.h"
#include <cmath>

#define d2r(angleDegrees) (angleDegrees * M_PI / 180.0)

typedef enum dimension {X, Y, Z} Dimension;

typedef struct point3d {
	GLfloat x, y, z;
} Point3D;

GLfloat distance(const Point3D* p, const Point3D* q);
void printPoint(const Point3D p);
void rotate(const Point3D* fixed, Point3D* target, double theta, Dimension dim);


typedef struct point2d {
	GLfloat x, y;
} Point2D;

//GLfloat distance(const Point2D* p, const Point2D* q);
#endif
