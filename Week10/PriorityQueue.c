#include <stdio.h>
#include <stdbool.h>
// Heap decl START-----------------------
#define MAX_HEAP    100
typedef char Data;

typedef struct
{
    Data data;
    int priority;
} HNode;

typedef struct 
{
    HNode items[MAX_HEAP + 1];
    int num;
} Heap;

// Make a heap empty
void InitHeap(Heap* pheap);
// check whether a heap is empty
bool IsEmpty(Heap* pheap);
// check whether a heap is full
bool IsFull(Heap* pheap);

// Insert a node to the heap
void Insert(Heap* pheap, Data data, int priority);
// Remove the maximum data from the heap (highest priority node)
Data Delete(Heap* pheap);

// Get a parent index for a given index
int GetParent(int idx);
// Get a left child index for a given index
int GetLChild(int idx);
// Get a right child index for a given index
int GetRChild(int idx);
// Get a child index with high priority between two child nodes
int GetHighPriorityChild(Heap* pheap, int idx);
// Heap decl END---------------------------------

// PQ decl START-----------------------------------
// Based on heap

typedef Heap PQueue;

void InitPQueue(PQueue* ppqueue);
bool IsPQEmpty(PQueue* ppqueue);
bool IsPQFull(PQueue* ppqueue);

// Insert an item to the priority queue
void EnQueue(PQueue* ppqueue, Data data, int priority);
// Delete an item to the priority queue
Data DeQueue(PQueue* ppqueue);
// PQ decl END------------------------------------


// Heap def START------------------------------------
// Make a heap empty
void InitHeap(Heap* pheap)
{
    pheap->num = 0;
}
// check whether a heap is empty
bool IsEmpty(Heap* pheap)
{
    return pheap->num == 0;
}
// check whether a heap is full
bool IsFull(Heap* pheap)
{
    return pheap->num == MAX_HEAP;
}

// Insert a node to the heap
void Insert(Heap* pheap, Data data, int priority)
{
    HNode newNode;
    int idx = pheap->num + 1;
    if (IsFull(pheap)) exit(1);

    // Compare the new node with its parent
    while (idx > 1) // we dispose 0 idx as blank, so it means idx == 1?
    {
        int parent = GetParent(idx);
        if (priority > pheap->items[parent].priority)
        {
            pheap->items[idx] = pheap->items[parent]; // parent has lower priority, exchange
            idx = parent;
        }
        else break;
    }
    newNode.data = data;
    newNode.priority = priority;

    pheap->items[idx] = newNode;
    pheap->num++;
}
// Remove the maximum data from the heap (highest priority node)
Data Delete(Heap* pheap)
{
    Data max = pheap->items[1].data;
    HNode last = pheap->items[pheap->num];
    int parent = 1, child; // 1 is root index
    // Compare the root with its child nodes
    while (child = GetHighPriorityChild(pheap, parent))
    {
        if (last.priority < pheap->items[child].priority)
        {
            pheap->items[parent] = pheap->items[child];
            parent = child;
        }
        else break;
    }

    pheap->items[parent] = last;
    pheap->num--;

    return max;
}

// Get a parent index for a given index
int GetParent(int idx)
{
    return idx / 2;
}
// Get a left child index for a given index
int GetLChild(int idx)
{
    return idx * 2;
}
// Get a right child index for a given index
int GetRChild(int idx)
{
    return idx * 2 + 1;
}
// Get a child index with high priority between two child nodes
int GetHighPriorityChild(Heap* pheap, int idx)
{
    if (GetLChild(idx) > pheap->num) // No child nodes exist
        return 0;
    else if (GetLChild(idx) == pheap->num) // Exist a left node only
        return GetLChild(idx);
    else // Choose a child node with the highest priority
    {
        int left = GetLChild(idx), right = GetRChild(idx);
        if (pheap->items[left].priority > pheap->items[right].priority)
            return left;
        else
            return right;
    }
}
// Heap def END----------------------------------

void InitPQueue(PQueue* ppqueue)
{
    InitHeap(ppqueue);
}
bool IsPQEmpty(PQueue* ppqueue)
{
    return IsEmpty(ppqueue);
}
bool IsPQFull(PQueue* ppqueue)
{
    return IsFull(ppqueue);
}

// Insert an item to the priority queue
void EnQueue(PQueue* ppqueue, Data data, int priority)
{
    Insert(ppqueue, data, priority);
}
// Delete an item to the priority queue
Data DeQueue(PQueue* ppqueue)
{
    return Delete(ppqueue);
}