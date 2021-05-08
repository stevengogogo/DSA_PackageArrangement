#ifndef TEST_LINKEDLIST_H
#define TEST_LINKEDLIST_H

#include "list.h"

void test_init(void){
    packData pd = init_packData(100,100);
    kill_packData(pd);
}

void test_linklist(void){
    packData pd = init_packData(100,100);

    for(int i=0;i<40;i++)
        _insertlist(&pd.lines[0].list, &pd.packs[i]);

    for(int i=40;i<80;i++)
        _insertlist(&pd.lines[23].list, &pd.packs[i]);

    for(int i=1;i<100;i++){
        _mergelist(&pd.lines[0].list, &pd.lines[i].list);
        
        TEST_CHECK(pd.lines[i].list.first == NULL);
        TEST_CHECK(pd.lines[i].list.last == NULL);
    }

    _popFirst(&pd.lines[0].list);

    for(int i=1;i<80;i++)
        _popLast(&pd.lines[0].list);


    kill_packData(pd);

    pd = init_packData(100,100);

    _mergelist(&pd.lines[0].list, &pd.lines[1].list);

    for(int i=0;i<101;i++)
        _insertlist(&pd.lines[1].list, &pd.packs[i]);

    for(int i=0;i<101;i++)
        _popFirst(&pd.lines[1].list);

    TEST_CHECK(pd.lines[0].list.first == NULL);
    TEST_CHECK(pd.lines[0].list.last == NULL);
    TEST_CHECK(pd.lines[1].list.first == NULL);
    TEST_CHECK(pd.lines[1].list.last == NULL);

    kill_packData(pd);
}


#endif