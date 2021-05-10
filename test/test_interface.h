#ifndef TEST_INTERFACE_H
#define TEST_INTERFAXCE_H

#include "acutest.h"
#include "list.h"

void test_stringOp(void){
    char a[20] = "push";
    TEST_CHECK(_getopID(a) == PUSH);
    TEST_CHECK(_getopID("merge") == MERGE);
}



#endif