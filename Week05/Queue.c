#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_QUEUE   100
typedef int Data;

typedef struct
{
    int front, rear;
    Data items[MAX_QUEUE];
} Queue;

// Make a queue empty
void InitQueue(Queue *pqueue);
// Check whether a queue is full
bool IsFull(Queue *pqueue);
// Check whether a queue is empty
bool IsEmpty(Queue *pqueue);

// Read the item at the front
Data Peek(Queue *pqueue);
// Insert an item at the rear
void EnQueue(Queue *pqueue, Data item);
// Delete an item at the front
Data DeQueue(Queue *pqueue);

int main(void)
{
    Queue queue;
    int i;
    InitQueue(&queue);
    for (i = 0; i < MAX_QUEUE - 1; i++)
    {
        printf("%d loop\n", i);
        int a;
        char b;
        scanf("%d", &a);
        EnQueue(&queue, a);
        printf("Y/N \n");
        scanf(" %c", &b);
        if (b == 'y' || b == 'Y')
            printf("%d\n", DeQueue(&queue));
    }
    return 0;
}

void InitQueue(Queue *pqueue)
{
    pqueue->front = pqueue->rear = 0;
}

bool IsFull(Queue *pqueue) // 애초에 한칸을 못 쓰는 상태, full 과 empty 를 구분하기 위함
{
    return pqueue->front == (pqueue->rear + 1) % MAX_QUEUE;
}

bool IsEmpty(Queue *pqueue)
{
    return pqueue->front == pqueue->rear;
}

Data Peek(Queue *pqueue)
{
    if (IsEmpty(pqueue))
        exit(1);
    return pqueue->items[pqueue->front];
}

void EnQueue(Queue *pqueue, Data item)
{
    if (IsFull(pqueue))
        exit(1);
    pqueue->items[pqueue->rear] = item;
    pqueue->rear = (pqueue->rear + 1) % MAX_QUEUE;
}

Data DeQueue(Queue *pqueue)
{
    Data result;
    if (IsEmpty(pqueue))
        exit(1);
    result = pqueue->items[pqueue->front];
    pqueue->front = (pqueue->front + 1) % MAX_QUEUE;
    return result;
}