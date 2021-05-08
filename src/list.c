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
    for(int i=0;i<=pd.N_Package;i++){
        pd.packs[i] = pk;
        pd.packs->ID = i;
    }

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

//Linked list 

void _insertlist(List* list, pack* pk){
    //Check pk is new
    assert(pk->avail == 0);
    assert(pk->next==NULL);
    assert(pk->prev==NULL);

    if (list->first == NULL){ // Init
        assert(list->last == NULL);
        list->first = pk;
        list->last = pk;
    }
    else{ // Continue
        assert(list->last->next == NULL);
        list->last->next = pk;
        pk->prev = list->last;
        list->last = pk;
    }

    pk->avail = 1; 
}

void _mergelist(List* listDst, List* listSrc){

    if (listSrc->first==NULL){ //src is null
        //Do nothing
    }
    else if (listDst->first == NULL){ //dst is null
        listDst->first = listSrc->first;
        listDst->last = listDst->last;
    }
    else{
    assert(listSrc->last != NULL);
    assert(listDst->last != NULL);

    //wiring dst end
    listDst->last->next = listSrc->first;
    listSrc->first->prev = listDst->last;

    //update dst end
    listDst->last = listSrc->last;
    
    //Clear source
    listSrc->first = NULL;
    listSrc->last = NULL;
    
    }
}


int _popFirst(List* list){
    assert(list->first!=NULL);
    int val = list->first->ID;

    //Rewiring
    list->first->avail = 0; // update availability
    list->first = list->first->next; // move start
    list->first->prev = NULL; // link start.prev to NULL

    if(list->last == list->first) //turn to null
        list->last = list->first;
    return val;
}

int _popLast(List* list){
    assert(list->first!=NULL);
    int val = list->last->ID;


    if(list->first == list->last){ //turn to null
        list->first = NULL;
        list->last = NULL;
        
    }

    else{

    //Rewiring
    list->last->avail = 0; // update availability
    list->last = list->last->prev; // move end
    list->last->next = NULL; // link end.next to NULL

    if(list->first == list->last) //turn to null
        list->first = list->last;

    }

    return val;
}


//Struct

pack getNullPack(void){
    pack pk;
    pk.avail = 0;
    pk.prev = NULL;
    pk.next = NULL;
    pk.ID = INT_MIN;
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