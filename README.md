# Package Arrangement

Keywords: `Queue`, `Stack`, `Binary Tree (search, insert, delete, remove, balance)`

## Usage

See [Problem Statement](Problem.pdf)

## Problem statements

- `L` production lines
- `N` packages
- `O` Operations


## Strategy

![image](https://user-images.githubusercontent.com/29009898/117527886-ce728680-b001-11eb-81c1-351902775993.png)


- Production line
  - Binomial Max Heap
    - Doubly linked list
  - Deque
    - First-in-First out
    - Doubly Linked list
      ```julia
      struct
        int[] array
        int* next_array
        int* prev_array
      end
      ```
      ![image](https://user-images.githubusercontent.com/29009898/117526184-0378dc00-aff6-11eb-9412-193ce3edf516.png)

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


## Free a binary tree

```
deallocate (node):
    //do nothing if passed a non-existent node
    if node is null
        return

    //now onto the recursion
    deallocate(left node)
    deallocate(right node)

    free node
```

Ref: [stackoverflow](https://stackoverflow.com/questions/9181146/freeing-memory-of-a-binary-tree-c)


## Returning a void function

Ref: [web](https://www.cs.fsu.edu/~cop3014p/lectures/ch7/index.html)

## References
1. Stack, Queue and Heap. [[GitBook](https://stephanosterburg.gitbook.io/scrapbook/coding/coding-interview/data-structures/heaps-stacks-queues)]
2.
