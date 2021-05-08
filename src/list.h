#ifndef LIST_H
#define LIST_H

#include <stdlib.h>

/** * package */
typedef struct pack{
    int val; //height
    int avail; //available?
    struct pack* prev;
    struct pack* next;
} pack;

typedef struct List{
    pack* first;
    pack* last;
} List;

typedef struct hnode{
    struct hnode* parent;
    struct hnode* leaves[2]; 
    pack* key;
} hnode;

/** * Production line*/
typedef struct{
    List list;
    hnode* heap;
    int avail;
} prodLine;

typedef struct{
    int N_Package;
    int N_Lines;
    prodLine* lines;
    pack* packArr;
} packData;

// Initiation and Deletion

/**
 * @brief Initiate a package management problem
 * 
 * @param n number of packages
 * @param l number of lines
 * @return packData 
 */
packData init_Problem(int n, int l);
void kill_Problem(packData);

// Data management
pack PushPack(packData, int i);
pack MergeLines(packData, int dst, int src);

//Pop
pack PopFirstPack(packData, int i);
pack PopLastPack(packData, int i);
pack PopMaxPack(packData, int i);

// Peak Data
pack PeakFirstPack(packData, int i);
pack PeakLastPack(packData, int i);
pack PeakMaxPack(packData, int i);


// Heap operation
void _insertHeap(hnode* root);
void _mergeHeap(hnode* rootDst, hnode* rootSrc);
void _extractMaxHeap(hnode* root);
void _killHeap(hnode* root);

//Linked operation
void _insertlist(List);
void _mergelist(List);
void _poplist(List);







#endif LIST_H