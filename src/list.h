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
    List* list;
    hnode* heap;
    int avail;
} prodLine;


// Initiation and Deletion
pack* init_packArr(int n);
void kil_packArr(pack*);

// Manage Data
pack PushPack(prodLine);
pack MergeLines(prodLine dst, prodLine src);
pack PopFirstPack(prodLine);
pack PopLastPack(prodLine);
pack PopMaxPack(prodLine);

// Peak Data
pack PeakFirstPack(prodLine);
pack PeakLastPack(prodLine);
pack PeakMaxPack(prodLine);


// Heap operation
void _insertHeap(hnode* root);
void _mergeHeap(hnode* rootDst, hnode* rootSrc);
void _extractMaxHeap(hnode* root);

//Linked operation
void _insertlist(List);
void _mergelist(List);
void _poplist(List);







#endif LIST_H