# Package Arrangement

Keywords: `Queue`, `Stack`, `Binary Tree (search, insert, delete, remove, balance)`


## Problem statements

- `L` production lines
- `N` packages
- `O` Operations


## Strategy

- Production line
  - Binomial Max Heap
    - Doubly linked list
  - Deque
    - First-in-First out
    - Linked array
    ```julia
    struct
      int[] array
      int* next_array
    end
    ```

- Peaking a production line
  - `getFirst`: `O(1)`
  - `getLast`: `O(1)`
  - `getMax`: `O(1)`

- Operation
  - `PopFirst`: `O(n)`
  - `PopLast`: `O(n)`
  - `PopMax`: `O(log n)`

- Merge Production line
  - Deque
## Queue


## Stack 


## Binary Tree Operation


### What is a "balanced" binary tree?



**Ref**: 
- [Balancing a binary search tree (GO)](https://appliedgo.net/balancedtree/)




## AVL Tree


**Ref**
- [Balancing a binary search tree (GO)](https://appliedgo.net/balancedtree/)
- [AVL Tree: Insertion (GreekforGeek)](https://www.geeksforgeeks.org/avl-tree-set-1-insertion/)
- [AVL Tree: Deletion (GreekforGeek)](https://www.geeksforgeeks.org/avl-tree-set-2-deletion/)
- [資料結構與演算法：AVL Tree](https://josephjsf2.github.io/data/structure/and/algorithm/2019/06/22/avl-tree.html)

### Time complexity with AVL Tree

|Operation|Time|
|:---:|:---:|
|Search|O(log n)|
|Insert|O(log n)|
|Delete|O(log n)|

- Advantage of using AVL Tree
  - Guarantee: O(log n) for binary search

**Ref**:
- [資料結構與演算法：AVL Tree](https://josephjsf2.github.io/data/structure/and/algorithm/2019/06/22/avl-tree.html)



## Idea

- Merge 要求 `log(n)`

## Hints

- 用 Heap: 快速找到 max, first, last
- Time complexity of merge: <O(n)
    - 方法: https://abitofcs.blogspot.com/2019/06/merging-heaps-in-olog-n.html
    - https://cs.stackexchange.com/questions/82793/merge-2-binary-heaps
    - https://medium.com/100-days-of-python/day-06-binomial-heap-88ca2edb8255
    - https://en.m.wikipedia.org/wiki/Binomial_heap


## References
1. Stack, Queue and Heap. [[GitBook](https://stephanosterburg.gitbook.io/scrapbook/coding/coding-interview/data-structures/heaps-stacks-queues)]
2.
