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
    pack* pk = NULL;
    pack* (*fun[3])(packData, int)=  {PeekFirstPack, 
                                        PeekLastPack, 
                                        PeekMaxPack};

    for (int i=1;i<=20;i++)
        PushPack(pd, i-1, i);
    
    for (int i=0;i<3;i++){
        pk = (*fun[i])(pd, 0);
        
    }

    for (int i=0;i<3;i++){
        pk = (*fun[i])(pd, 99);
    }
    

    kill_packData(pd);

    return 0;
}