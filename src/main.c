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

    for(int i=0;i<40;i++)
        _insertlist(&pd.lines[0].list, &pd.packs[i]);

    for(int i=40;i<80;i++)
        _insertlist(&pd.lines[23].list, &pd.packs[i]);

    for(int i=1;i<100;i++){
        _mergelist(&pd.lines[0].list, &pd.lines[i].list);
        
    
    }

    _popFirst(&pd.lines[0].list);

    for(int i=1;i<80;i++)
        _popLast(&pd.lines[0].list);

    _mergelist(&pd.lines[0].list, &pd.lines[1].list);
    
    for(int i=0;i<101;i++)
        _insertlist(&pd.lines[1].list, &pd.packs[i]);

    for(int i=0;i<101;i++)
        _popFirst(&pd.lines[1].list);
    return 0;
}