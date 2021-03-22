#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef char Data;

typedef struct
{
    int front, rear;
    Data* items;
} Queue;

void InitQueue(Queue *pqueue, const int MAX_QUEUE);
void DeleteQueue(Queue *pqueue);
bool IsFull(const Queue *pqueue, const int MAX_QUEUE);
bool IsEmpty(const Queue *pqueue);

Data Peek(const Queue *pqueue);
void EnQueue(Queue *pqueue, const int numOfNew, const int MAX_QUEUE);
void DeQueue(Queue *pqueue, const int numOut, const int MAX_QUEUE);

int EmptySpace(const Queue *pqueue, const int MAX_QUEUE);
bool CanEnter(const Queue *pqueue, const int numOfNew, const int MAX_QUEUE);
void AmusementPark(void);

int main(void)
{
    AmusementPark();
    return 0;
}

void InitQueue(Queue *pqueue, const int MAX_QUEUE)
{
    pqueue->items = (Data *)malloc( sizeof(Data) * (MAX_QUEUE + 1) );
    pqueue->front = pqueue->rear = 0;
}

void DeleteQueue(Queue *pqueue)
{
    free(pqueue->items);
}

bool IsFull(const Queue *pqueue, const int MAX_QUEUE)
{
    return ( (pqueue->rear + 1) % (MAX_QUEUE + 1) ) == pqueue->front;
}

bool IsEmpty(const Queue *pqueue)
{
    return pqueue->front == pqueue->rear;
}

Data Peek(const Queue *pqueue)
{
    if (IsEmpty(pqueue))
        exit(1);
    return pqueue->items[pqueue->front];
}

void EnQueue(Queue *pqueue, const int numOfNew, const int MAX_QUEUE)
{
    if (IsFull(pqueue, MAX_QUEUE))
        exit(1);
    pqueue->rear = (pqueue->rear + numOfNew) % (MAX_QUEUE + 1);
}

void DeQueue(Queue *pqueue, const int numOut, const int MAX_QUEUE)
{
    if (IsEmpty(pqueue))
        exit(1);
    pqueue->front = (pqueue->front + numOut) % (MAX_QUEUE + 1);
}

int EmptySpace(const Queue *pqueue, const int MAX_QUEUE)
{
    if (pqueue->rear >= pqueue->front)
        return MAX_QUEUE - (pqueue->rear - pqueue->front);
    else
        return MAX_QUEUE - ((MAX_QUEUE + pqueue->rear + 1) - pqueue->front);
}

bool CanEnter(const Queue *pqueue, const int numOfNew, const int MAX_QUEUE)
{
    return EmptySpace(pqueue, MAX_QUEUE) >= numOfNew;
}

void AmusementPark(void)
{
    Queue queue;
    int n, c, t;
    int* newHistory;
    int i;
    scanf("%d %d %d\n", &n, &c, &t);
    InitQueue(&queue, c);
    newHistory = (int *)malloc( sizeof(int) * t );
    
    for (i = 0; i < n; i++)
    {
        int numOfNew;
        if (i >= t && !IsEmpty(&queue))
            DeQueue(&queue, newHistory[i % t], c);

        scanf("%d", &numOfNew);
        if (CanEnter(&queue, numOfNew, c))
        {
            EnQueue(&queue, numOfNew, c);
            newHistory[i % t] = numOfNew;
            printf("%s", (i < n - 1) ? "1 " : "1\n");
        }
        else
        {
            newHistory[i % t] = 0;
            printf("%s", (i < n - 1) ? "0 " : "0\n");
        }
    }


    DeleteQueue(&queue);
    free(newHistory);
}
