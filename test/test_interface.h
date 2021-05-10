#ifndef TEST_INTERFACE_H
#define TEST_INTERFAXCE_H

#include "acutest.h"
#include "list.h"

void test_stringOp(void){
    char a[20] = "push";
    TEST_CHECK(getopID(a) == PUSH);
    TEST_CHECK(getopID("merge") == MERGE);
}



#endif