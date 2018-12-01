#ifndef COMMON_H
#define COMMON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <climits>
#include <string>
#include <chrono>
#include <vector>
#include <cstddef>
#include <cstring>

/* Timing */
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

/* Perspective defaults */
#define PERS_DEF_ANGLE 45
#define PERS_DEF_ASPECT 1
#define PERS_DEF_NEAR  0.01f
#define PERS_DEF_FAR    1.0f

/* Camera defaults */
#define  CAM_DEF_LOC_X 0.0f
#define  CAM_DEF_LOC_Y 1.2f
#define  CAM_DEF_LOC_Z 0.3f
#define  CAM_DEF_FOC_X 0.0f
#define  CAM_DEF_FOC_Y 1.2f
#define  CAM_DEF_FOC_Z 0.0f
#define  CAM_DEF_UP_X 0.0f
#define  CAM_DEF_UP_Y 1.0f
#define  CAM_DEF_UP_Z 0.0f

/* Datatypes */
#define int_u8 	unsigned char
#define int_8  	char
#define int_u16 unsigned short
#define int_16	short

/**
 * Tokenize a string
 * @param text text you want tokenized
 * @param delim delimiter for tokenization
 * @return tokens
 */
std::vector<std::string> tokenize(std::string text, std::string delim);

/**
 * C++ requires you to reinvent the wheel
 */
bool stringIsInteger(std::string s);

/**
 * ditto
 */
bool stringIsNumber(std::string s);

#endif
