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
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define INT_MIN -2147483647
#define EMPTY -23432
#define PUSH -232310
#define MERGE -2323
#define MAX_Q 200000
#define MAX_N 200000
#define MAX_OP_CHAR 20

/** * package */
struct packData;

typedef struct pack{
    int avail; //available?
    struct pack* prev;
    struct pack* next;
    int ID;
    int (*popfunc)(struct packData, int);
    int line;
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

typedef struct packData{
    int N_Package;
    int N_Lines;
    prodLine* lines;
    pack* packs;
} packData;



typedef struct{
    int opID;
    int arg[2];
} query;

//Solve
int solve(packData pd, query* qs, int* pkOrders);

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
void PushPack(packData, int iLine, int iPack);
void MergeLines(packData, int iDst, int iSrc);

//Pop
int PopFirstPack(packData, int iLine);
int PopLastPack(packData, int iLine);
int PopMaxPack(packData, int iLine);
/** * Use Function pointer to generalize the Pop operation*/
int _PopOperation(packData, int,int (*PeekFunc)(packData,int), int (*PopFunc)(packData,int));

// Peak Data
/** * Peek first. Return NULL if the line is empty*/
int PeekFirstPack(packData, int i);
/** * Peek Last. Return NULL if the line is empty*/
int PeekLastPack(packData, int i);
int PeekMaxPack(packData, int i);

/** Array of peek functions*/
static const int (*PEEKFUNC[3])(packData, int) = {PeekFirstPack, PeekLastPack, PeekMaxPack};
void _clearGetMethod(packData, int iLine);
void _setGetMethod(packData, int iLine);


// Heap operation
void _insertHeap(packData pd, int iLine, int iPack);
int _popMaxHeap(packData, int iLine);
void _mergeHeap(packData, int iDst, int iSrc);

/** @brief Max heapidity from below the input node
 * @return the destination leaf
*/
hnode* _maxHeapify(hnode*);
hnode* _create_node(hnode* parent, pack* key);
/** * Return index of Null leave. -1 for occupied */
int _findNullLeave(hnode* node);
int _findActLeave(hnode* node);
void _swapPackageHeap(hnode* a, hnode* b);
void _deleteLeaf(hnode* leaf);
void _killHeap(hnode* root);

//Linked list 

void _insertlist(packData pd, int iLine, int iPack);
void _mergelist(packData, int iDst, int iSrc);
/**
 * @brief Pop first item. Set popped item.avail (@ref pack) to zero.
 * @note this function can be used to pop item. No matter it is availability or not. The item's availablity will be set as 0.
 * @return int popped ID
 */
int _popFirst(packData pd, int iLine);
/**
 * @brief Similar to @ref _popFirst .
 */
int _popLast(packData pd, int iLine);


//Remove Item
void _removePack(pack*);
void _removePackGetMethod(pack*);

//Struct
pack getNullPack(void);
prodLine getNullProdLine(void);

//Interface
int _getopID(char*);
void _getOperation(query*);
void _printRes(int sol);
void interface(void);

#endif 