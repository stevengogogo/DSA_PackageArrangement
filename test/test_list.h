#ifndef TEST_LINKEDLIST_H
#define TEST_LINKEDLIST_H

#include "list.h"

void test_init(){
    packData pd = init_packData(100,100);
    kill_packData(pd);
}


#endif