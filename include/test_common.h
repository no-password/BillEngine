#ifndef TEST_COMMON_H
#define TEST_COMMON_H

#include <cstdlib>
#include <cassert>

#ifdef CXX_MSVC
#define _FNAME_ __FUNCTION__
#else
#define _FNAME_ __func__
#endif

#endif
