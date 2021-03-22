#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;

typedef struct _Node
{
    Data item;
    struct _Node* next;
} Node;

typedef struct
{
    Node* front;
    Node* rear;
} DQueue;

// Make a queue empty
void InitQueue(DQueue *pqueue);
// Check whether a queue is empty.
bool IsEmpty(DQueue *pqueue);

// Read the item at the front
Data Peek(DQueue *pqueue);
// Insert an item at the rear
void EnQueue(DQueue *pqueue, Data item);
// Delete an item at the front
void DeQueue(DQueue *pqueue);

int main(void)
{

    return 0;
}

void InitQueue(DQueue *pqueue)
{
    pqueue->front = pqueue->rear = NULL;
}

bool IsEmpty(DQueue *pqueue)
{
    return pqueue->front == NULL;
}

Data Peek(DQueue *pqueue)
{
    if (IsEmpty(pqueue)) exit(1);

    return pqueue->front->item;
}

void EnQueue(DQueue *pqueue, Data item)
{
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;

    if (IsEmpty(pqueue))
        pqueue->front = pqueue->rear = newNode;
    else
    {
        pqueue->rear->next = newNode;
        pqueue->rear = newNode;
    }
}

void DeQueue(DQueue *pqueue)
{
    Node* temp;
    if (IsEmpty(pqueue)) exit(1);

    temp = pqueue->front;
    if (temp->next == NULL) // is there only one in queue?
        pqueue->front = pqueue->rear = NULL;
    else
        pqueue->front = temp->next;
    free(temp);
}