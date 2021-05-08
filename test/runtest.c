#include <stdio.h>

#include "acutest.h"

#include "test_utils.h"
#include "test_list.h"


// Run TESTs 
TEST_LIST = {
    {"Utility", test_utils},
    {"linked list", test_list},
    {NULL, NULL} // Terminate the test
};