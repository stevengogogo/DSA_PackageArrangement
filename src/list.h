/**
 * @file list.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-05-08
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define INT_MIN -2147483647

/** * package */
typedef struct pack{
    int avail; //available?
    struct pack* prev;
    struct pack* next;
    int ID;
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
    pack* packs;
} packData;


// Initiation and Deletion

/**
 * @brief Initiate a package management problem
 * 
 * @param n number of packages
 * @param l number of lines
 * @return packData 
 */
packData init_packData(int n, int l);
void kill_packData(packData);

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
void _insertHeap(hnode* root, pack*);
int _popMaxHeap(hnode* root);
void _mergeHeap(hnode* rootDst, hnode* rootSrc);
void _killHeap(hnode* root);

//Linked list 

void _insertlist(List*, pack*);
void _mergelist(List* dst, List* src);
/**
 * @brief Pop first item. Set popped item.avail (@ref pack) to zero.
 * @note this function can be used to pop item. No matter it is availability or not. The item's availablity will be set as 0.
 * @return int popped ID
 */
int _popFirst(List*);
/**
 * @brief Similar to @ref _popFirst .
 */
int _popLast(List*);


//Struct
pack getNullPack(void);
prodLine getNullProdLine(void);




#endif 