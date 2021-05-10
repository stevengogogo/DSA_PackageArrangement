#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "acutest.h"
#include "utils.h"

void test_utils(void)
{
   TEST_CHECK(argMin(-1212,3) == 0);
   TEST_CHECK(argMin(3, -1212) == 1);
   TEST_CHECK(argMin(-1212,-1212) == 1);
}


#endif