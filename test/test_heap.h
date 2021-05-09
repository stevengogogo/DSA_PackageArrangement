#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#include "list.h"
#include "acutest.h"

void test_heap(void){
    packData pd = init_packData(100,100);

    //Heap insertion
    for (int i=1;i<=40;i++){
        _insertHeap(pd, 0, &pd.packs[i]);
    }

    //Heap extraction
    for (int i=40;i>=1;i--){
        TEST_CHECK(i == _popMaxHeap(pd, 0) );
        TEST_MSG("Exp: %d ; Got: %d",i, _popMaxHeap(pd, 0));
    }

    TEST_CHECK(pd.lines[0].heap == NULL);

    kill_packData(pd);
}



#endif