#include <stdio.h>

#include "acutest.h"


#include "test_heap.h"
#include "test_utils.h"
#include "test_list.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"problem initiation", test_init},
    {"linked list", test_linklist},
    {"Heap", test_heap},
    {NULL, NULL} // Terminate the test
};