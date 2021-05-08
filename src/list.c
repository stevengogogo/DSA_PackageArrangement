#include "list.h"

packData init_packData(int n, int l){
    packData pd;

    pd.N_Lines = l;
    pd.N_Package = n;

    //Create NULL pack
    pack pk = getNullPack();
    //Create Null prodLine;
    prodLine pl = getNullProdLine();

    //Memory
    size_t sizePacks = (pd.N_Package + 1)*sizeof(pack); //[0,1,n]
    size_t sizeLines = pd.N_Lines*sizeof(prodLine);  //[0,l-1]

    // Allocate 
    pd.packs = (pack*)malloc(sizePacks);
    pd.lines = (prodLine*)malloc(sizeLines);

    // initialize
    for(int i=0;i<=pd.N_Package;i++)
        pd.packs[i] = pk;

    for(int i=0;i<pd.N_Lines;i++)
        pd.lines[i] = pl;


    return pd;
}

void kill_packData(packData pd){
    //kill heaps
    for(int i=0;i<pd.N_Lines;i++)
        _killHeap(pd.lines[i].heap);
    
    free(pd.lines);
    free(pd.packs);
}


//Heap


void _killHeap(hnode* root){
    if (root == NULL)
        return ;
        
    _killHeap(root->leaves[0]);
    _killHeap(root->leaves[1]);

    free(root);
}


//Struct

pack getNullPack(void){
    pack pk;
    pk.avail = 0;
    pk.prev = NULL;
    pk.next = NULL;
    return pk;
}

prodLine getNullProdLine(void){
    prodLine pl;
    pl.heap = NULL;
    pl.avail = 0;
    pl.list.first = NULL;
    pl.list.last = NULL;
    return pl;
}