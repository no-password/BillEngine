#ifndef COMMON_H_INCLUDED
#define COMMON_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <climits>
#include <string>
#include <chrono>

/* Timing */
typedef std::chrono::high_resolution_clock Time;
typedef std::chrono::duration<float> fsec;

/* Camera defaults */
#define  CAM_DEF_LOC_X 0.0f
#define  CAM_DEF_LOC_Y 0.6f
#define  CAM_DEF_LOC_Z 0.3f
#define  CAM_DEF_FOC_X 0.0f
#define  CAM_DEF_FOC_Y 0.6f
#define  CAM_DEF_FOC_Z 0.0f
#define  CAM_DEF_UP_X 0.0f
#define  CAM_DEF_UP_Y 1.0f
#define  CAM_DEF_UP_Z 0.0f

#endif
