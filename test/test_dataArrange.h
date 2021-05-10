#ifndef TEST_DATAARRANGE_H
#define TEST_DATAARRANGE_H

#include "list.h"
#include "acutest.h"

void test_peek(void){
    packData pd = init_packData(100,100);
    pack* pk = NULL;
    pack* (*fun[3])(packData, int)=  {PeekFirstPack, 
                                        PeekLastPack, 
                                        PeekMaxPack};

    for (int i=1;i<=20;i++)
        PushPack(pd, i-1, i);
    
    for (int i=0;i<3;i++){
        pk = (*fun[i])(pd, 0);
        TEST_CHECK(pk->ID==1);
    }

    for (int i=0;i<3;i++){
        pk = (*fun[i])(pd, 99);
        TEST_CHECK(pk==NULL);
    }
    

    kill_packData(pd);
}



#endif