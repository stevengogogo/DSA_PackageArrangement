/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "list.h" 

int main()
{

    packData pd = init_packData(100,100);
    int a = 0;
    //Heap insertion
    for (int i=1;i<=40;i++){
        _insertHeap(pd, 0, i);
    }

    //Heap extraction
    for (int i=40;i>=1;i--){
        a = _popMaxHeap(pd, 0);
    }

    kill_packData(pd);

    return 0;
}