#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_list.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"problem initiation", test_init},
    {NULL, NULL} // Terminate the test
};