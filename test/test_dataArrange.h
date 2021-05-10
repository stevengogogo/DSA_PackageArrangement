#ifndef TEST_DATAARRANGE_H
#define TEST_DATAARRANGE_H

#include "list.h"
#include "acutest.h"

void test_peek(void){
    packData pd = init_packData(100,100);
    pack* pk = NULL;
    int (*fun[3])(packData, int)=  {PeekFirstPack, PeekLastPack, PeekMaxPack};

    for (int i=1;i<=20;i++)
        PushPack(pd, i-1, i);
    
    for (int i=0;i<3;i++){
        TEST_CHECK((*fun[i])(pd, 0)==1);
    }

    for (int i=0;i<3;i++){
        TEST_CHECK((*fun[i])(pd, 99)==EMPTY);
    }
    

    for(int i=19;i>0;i--){
        MergeLines(pd, 0, i);
    }


    TEST_CHECK(PeekFirstPack(pd, 0)==1);
    TEST_CHECK(PeekLastPack(pd, 0)==2);
    TEST_CHECK(PeekMaxPack(pd, 0)==20);

    kill_packData(pd);
}



#endif