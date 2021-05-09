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

hnode* _insertHeap(hnode* root, pack* pk){
    assert(pk->avail == 0);
    pk->avail = 1; //update availibility

    hnode* heapRoot = NULL;
    hnode* curNode = NULL;
    pack* minPK = pk;
    pack* tmp;
    int availLeafID = -1;//[0,1,-1]
    int nextDir = 0;//[0,1]

    if (root==NULL){//first element
        root = create_node(NULL, pk);
        heapRoot = root;
        return heapRoot;
    }
    else{
        curNode = root; //current node
        heapRoot = root;
    }

    while(curNode != NULL){

        //swap minimum
        if (minPK->ID > curNode->key->ID){ 
            tmp = curNode->key;
            curNode->key = minPK;
            minPK = tmp;
        }

        //Find available leaves
        availLeafID = _findNullLeave(curNode);

        if (availLeafID != -1){ //available site
            curNode->leaves[availLeafID] = create_node(curNode, minPK);
            break;
        }
        else{ // move to the minimum leaf
            nextDir =  argMin(curNode->leaves[0]->key->ID, 
                              curNode->leaves[1]->key->ID);
            curNode = curNode->leaves[nextDir];
        }

    }

    return heapRoot;
}


int _popMaxHeap(hnode* root){
    assert(root != NULL);
    hnode* curNode = root;
    hnode* nextNode = NULL;
    int actLeafID = _findActLeave(curNode);
    int val = root->key->ID;
    root->key->avail = 0;
    
    pack pkInf = getNullPack(); //Package with minius infinity
    pkInf.ID = INT_MIN;
    root->key = &pkInf;

    while( actLeafID != -1 ){ //There is at least a leave
        nextNode = curNode->leaves[actLeafID];
        _swapPackageHeap(curNode, nextNode);
        curNode = nextNode; // move to a actual leaf
        actLeafID = _findActLeave(curNode);
    }

    //delete node
    free(curNode);

    return val;
}

hnode* create_node(hnode* parent, pack* key){
    hnode* newnode = (hnode*)malloc(sizeof(hnode));
    newnode->key = key;
    newnode->parent = parent;
    newnode->leaves[0] = NULL;
    newnode->leaves[1] = NULL;
    return newnode;    
}

int _findNullLeave(hnode* node){
    if (node->leaves[0] == NULL){
        return 0;
    }
    else if(node->leaves[1] == NULL){
        return 1;
    }
    else{
        return -1;
    }
}

int _findActLeave(hnode* node){
    if (node->leaves[0] != NULL){
        return 0;
    }
    else if(node->leaves[1] != NULL){
        return 1;
    }
    else{
        return -1;
    }
}

void _swapPackageHeap(hnode* a, hnode* b){
    pack* tmp = a->key;
    a->key = b->key;
    b->key = tmp;
}

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
    list->first->avail = 0; // update availability

    if(list->first == list->last){ //turn to null
        list->first = NULL;
        list->last = NULL;
        
    }
    else{
    //Rewiring
    list->first = list->first->next; // move start
    list->first->prev = NULL; // link start.prev to NULL

    if(list->last == list->first) //turn to null
        list->last = list->first;

    }

    return val;
}

int _popLast(List* list){
    assert(list->first!=NULL);
    int val = list->last->ID;
    list->last->avail = 0; // update availability

    if(list->first == list->last){ //turn to null
        list->first = NULL;
        list->last = NULL;
        
    }

    else{
    //Rewiring
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