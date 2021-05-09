#ifndef TEST_HEAP_H
#define TEST_HEAP_H

#include "list.h"
#include "acutest.h"

void test_heap(void){
    packData pd = init_packData(100,100);

    //Heap insertion
    for (int i=1;i<40;i++){
        pd.lines[0].heap = _insertHeap(pd.lines[0].heap, &pd.packs[i]);
    }

    //Heap extraction
    for (int i=1;i<40;i++){
        _popMaxHeap(pd.lines[0].heap);
    }

    TEST_CHECK(pd.lines[0].heap == NULL);

    kill_packData(pd);
}



#endif