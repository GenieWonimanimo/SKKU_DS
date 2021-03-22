#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;

typedef struct
{
    int front, rear;
    Data* items;
} Queue;

void InitQueue(Queue *pqueue, const int pN);
void DeleteQueue(Queue *pqueue);
bool IsEmpty(const Queue *pqueue);

Data Peek(const Queue *pqueue);
void EnQueue(Queue *pqueue, const Data item);
void DeQueue(Queue *pqueue);

int NumberOfPeople(const Queue *pqueue);
bool CanEnter(const Queue *pqueue, const int pNumOfNew, const int pC);
void AmusementPark(void);

int main(void)
{
    AmusementPark();
    return 0;
}

void InitQueue(Queue *pqueue, const int pN)
{
    pqueue->items = (Data *)malloc( sizeof(Data) * pN );
    pqueue->front = pqueue->rear = 0;
}

void DeleteQueue(Queue *pqueue)
{
    free(pqueue->items);
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

void EnQueue(Queue *pqueue, Data item)
{
    pqueue->items[(pqueue->rear)++] = item;
}

void DeQueue(Queue *pqueue)
{
    if (IsEmpty(pqueue))
        exit(1);
    pqueue->front++;
}

int NumberOfPeople(const Queue *pqueue)
{
    int result = 0;
    int i;
    for (i = pqueue->front; i < pqueue->rear; i++)
        result += pqueue->items[i];
    return result;
}

bool CanEnter(const Queue *pqueue, const int pNumOfNew, const int pC)
{
    return (NumberOfPeople(pqueue) + pNumOfNew) <= pC;
}

void AmusementPark(void)
{
    Queue queue;
    int n, c, t;
    int i;
    scanf("%d %d %d", &n, &c, &t);
    InitQueue(&queue, n);
    for (i = 0; i < n; i++)
    {
        int numOfNew;
        scanf("%d", &numOfNew);

        if (i >= t && !IsEmpty(&queue))
            DeQueue(&queue);
        if (CanEnter(&queue, numOfNew, c))
        {
            printf("%s", (i < n - 1) ? "1 " : "1\n");
            EnQueue(&queue, numOfNew);
        }
        else
            printf("%s", (i < n - 1) ? "0 " : "0\n");
    }
    DeleteQueue(&queue);
}