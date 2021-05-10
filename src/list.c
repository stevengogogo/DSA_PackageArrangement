#include "list.h"

int solve(packData pd, query* qs, int* pkOrders){
    //TODO
}

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
        pd.packs[i].ID = i;
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

// Data management
void PushPack(packData pd, int iLine, int iPack){
    pack* pk = &pd.packs[iPack];
    assert(pk->avail == 0);

    _insertHeap(pd, iLine, iPack);
    _insertlist(pd, iLine, iPack);

    pk->avail = 1;
}

void MergeLines(packData pd, int iDst, int iSrc){
    assert(pd.lines[iSrc].avail==1);
    assert(pd.lines[iDst].avail==1);

    _mergeHeap(pd, iDst, iSrc);
    _mergelist(pd, iDst, iSrc);
    pd.lines[iSrc].avail = 0;
}


// Pop
int PopFirstPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekFirstPack, _popFirst);
}

int PopLastPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekLastPack, _popLast);
}

int PopMaxPack(packData pd, int iLine){
    return _PopOperation(pd, iLine, PeekMaxPack, _popMaxHeap);
}

int _PopOperation(packData pd, int iLine, int (*PeekFunc)(packData,int), int (*PopFunc)(packData,int)){
    int ID = (*PeekFunc)(pd, iLine);
    int ID_POP = (*PopFunc)(pd, iLine);
    assert(ID == ID_POP);
    pd.packs[ID].avail = 0;
    return ID_POP;
}

// Peek Data

int PeekFirstPack(packData pd, int i){
    if(pd.lines[i].list.first != NULL){
        while(pd.lines[i].list.first->avail == 0 && pd.lines[i].list.first != NULL)
            _popFirst(pd, i);
    }

    //Return
    if(pd.lines[i].list.first == NULL)
        return EMPTY;
    else 
        return pd.lines[i].list.first->ID;
}

int PeekLastPack(packData pd, int i){
    if(pd.lines[i].list.first != NULL){
        while(pd.lines[i].list.last->avail == 0 && pd.lines[i].list.first != NULL)
            _popLast(pd, i);
    }

    //Return
    if(pd.lines[i].list.last == NULL)
        return EMPTY;
    else 
        return pd.lines[i].list.last->ID;
}

int PeekMaxPack(packData pd, int i){
    if(pd.lines[i].heap != NULL){
        while(pd.lines[i].heap->key->avail == 0 && pd.lines[i].heap != NULL)
            _popMaxHeap(pd, i);
    }

    //Return
    if (pd.lines[i].heap == NULL)
        return EMPTY;
    else
        return pd.lines[i].heap->key->ID;
}



//Heap

void _insertHeap(packData pd, int iLine, int iPack){
    pack* pk = &pd.packs[iPack];
    hnode* root = pd.lines[iLine].heap;


    hnode* heapRoot = NULL;
    hnode* curNode = NULL;
    pack* minPK = pk;
    pack* tmp;
    int availLeafID = -1;//[0,1,-1]
    int nextDir = 0;//[0,1]

    if (root==NULL){//first element
        root = _create_node(NULL, pk);
        pd.lines[iLine].heap = root;
        return;
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
            curNode->leaves[availLeafID] = _create_node(curNode, minPK);
            break;
        }
        else{ // move to the minimum leaf
            nextDir =  argMin(curNode->leaves[0]->key->ID, 
                              curNode->leaves[1]->key->ID);
            curNode = curNode->leaves[nextDir];
        }

    }

}


int _popMaxHeap(packData pd, int i){
    hnode* root = pd.lines[i].heap;

    assert(root != NULL);
    hnode* curNode = root;

    int val = root->key->ID;
    root->key->avail = 0;

    //One element heap
    if (_findActLeave(root) == -1){
        free(root);
        pd.lines[0].heap = NULL;
        return val;
    }
    
    //Set root as minius infinity
    pack pkInf = getNullPack(); 
    pkInf.ID = INT_MIN;
    root->key = &pkInf;

    //Max heapidity
    curNode = _maxHeapify(curNode);

    //delete leaf
    _deleteLeaf(curNode);

    return val;
}

void _mergeHeap(packData pd, int iDst, int iSrc){

    pack pkInf = getNullPack(); 
    pkInf.ID = INT_MIN;
    hnode* root = _create_node(NULL, &pkInf);
    hnode* listD = pd.lines[iDst].heap;
    hnode* listS = pd.lines[iSrc].heap;

    assert(listD->parent==NULL);
    assert(listS->parent==NULL);

    //New root
    pd.lines[iDst].heap = root;
    //Link to heaps
    root->leaves[0] = listD;
    root->leaves[1] = listS;
    listD->parent = root;
    listS->parent = root;

    // Heapidy
    root = _maxHeapify(root);

    // Delete auxillary node
    _deleteLeaf(root);

    // Empty source
    pd.lines[iSrc].heap = NULL;
}



hnode* _maxHeapify(hnode* node){
    int actLeafID = _findActLeave(node);
    hnode* nextNode = NULL;
    hnode* curNode = node;
    int nextDir=0;

    while(actLeafID != -1){
        if(_findNullLeave(curNode) == -1){
            nextDir = 1^(argMin(curNode->leaves[0]->key->ID,         
                                curNode->leaves[1]->key->ID));
            nextNode = curNode->leaves[nextDir];
        }
        else{
            nextNode = curNode->leaves[actLeafID];
        }
        _swapPackageHeap(curNode, nextNode);
        curNode = nextNode;
        actLeafID = _findActLeave(curNode);
    }

    return curNode;
}

hnode* _create_node(hnode* parent, pack* key){
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

void _deleteLeaf(hnode* leaf){
    assert(leaf->leaves[0] == NULL);
    assert(leaf->leaves[1] == NULL);
    if (leaf->parent->leaves[0] == leaf){
        leaf->parent->leaves[0] = NULL;
    }
    else{
        leaf->parent->leaves[1] = NULL;
    }

    free(leaf);
    leaf = NULL;
}

void _killHeap(hnode* root){
    if (root == NULL)
        return ;
        
    _killHeap(root->leaves[0]);
    _killHeap(root->leaves[1]);

    free(root);
}



//Linked list 

void _insertlist(packData pd, int iLine, int iPack){
    List* list = &pd.lines[iLine].list;
    pack* pk = &pd.packs[iPack];

    //Check pk is new
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
}

void _mergelist(packData pd, int iDst, int iSrc){

    List* listDst = &pd.lines[iDst].list;
    List* listSrc = &pd.lines[iSrc].list;

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


int _popFirst(packData pd, int iLine){
    List* list = &pd.lines[iLine].list;
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

int _popLast(packData pd, int iLine){
    List* list = &pd.lines[iLine].list;
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
    pl.avail = 1;
    pl.list.first = NULL;
    pl.list.last = NULL;
    return pl;
}


//Interface
int _getopID(char* op){
    if(strcmp(op, "push")==0)
        return PUSH;
    else if(strcmp(op, "merge")==0)
        return MERGE;
    else 
        return -1;
}

void _getOperation(query* Op){
    char opStr[MAX_OP_CHAR];
    scanf("%s",opStr);
    scanf("%d", &Op->arg[0]);
    scanf("%d", &Op->arg[1]);
    Op->opID = _getopID(opStr);
}

void _printRes(int sol){
    if (sol == 1)
        printf("possible\n");
    else
        printf("impossible\n");
}

void interface(void){
    int T; // # of test cases
    int nP; // # of packages
    int nQ; // # of queries
    int nL; // # of Lines
    char opStr[20];
    int sol;
    query* Ops = (query*)malloc(MAX_Q * sizeof(query));
    int* pkOrders = (int*)malloc(MAX_N*sizeof(int));

    scanf("%d", &T);

    for(int t=0;t<T;t++){

        // Problem Info
        scanf("%d", &nP);
        scanf("%d", &nQ);
        scanf("%d", &nL);

        //Initiation
        packData pd = init_packData(nP, nL);

        //Operations
        for(int i=0;i<nQ;i++)
            _getOperation(&Ops[i]);

        //Save package order
        for(int i=0;i<nP;i++)
            scanf("%d", &pkOrders[i]);

        //Solve
        /*
        sol = solve(pd, Ops, pkOrders);
        _printRes(sol);
        */

        kill_packData(pd);
    }

    //Free
    free(Ops);
    free(pkOrders);
}