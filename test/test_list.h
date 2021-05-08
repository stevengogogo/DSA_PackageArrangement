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

    for(int i=41;i<80;i++)
        _insertlist(&pd.lines[23].list, &pd.packs[i]);

    for(int i=1;i<100;i++)
        _mergelist(&pd.lines[0].list, &pd.lines[i].list);

    _popFirst(&pd.lines[0].list);
    _popLast(&pd.lines[0].list);

    
    kill_packData(pd);
}


#endif