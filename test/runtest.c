#include <stdio.h>

#include "acutest.h"


#include "test_heap.h"
#include "test_utils.h"
#include "test_list.h"
#include "test_dataArrange.h"
#include "test_interface.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"problem initiation", test_init},
    {"linked list", test_linklist},
    {"Heap", test_heap},
    {"Heap Merge", test_heapMerge},
    {"Peek Data", test_peek},
    {"Test Get op ID", test_stringOp},
    {NULL, NULL} // Terminate the test
};