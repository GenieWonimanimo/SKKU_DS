#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef char Data;
typedef struct
{
    int front, rear;
    Data* items;
} Queue;


void InitQueue(Queue *pqueue, const Data pInitialState[], const int MAX_QUEUE);
void DeleteQueue(Queue *pqueue);
bool IsFull(const Queue *pqueue, const int MAX_QUEUE);
bool IsEmpty(const Queue *pqueue);

Data Peek(const Queue *pqueue);
void EnQueue(Queue *pqueue, const Data item, const int MAX_QUEUE);
void DeQueue(Queue *pqueue, const int MAX_QUEUE);

bool IsOnlyOne(const Queue *pqueue, const int MAX_QUEUE);
void PopAPointPencil(void);

int main(void)
{
    PopAPointPencil();
    return 0;
}

void InitQueue(Queue *pqueue, const Data pInitialState[], const int MAX_QUEUE)
{
    int i;
    pqueue->items = (Data *)malloc( sizeof(Data) * (MAX_QUEUE + 1) );
    pqueue->front = pqueue->rear = 0;
    for (i = 0; i < strlen(pInitialState); i++)
        EnQueue(pqueue, pInitialState[i], MAX_QUEUE);
}

void DeleteQueue(Queue *pqueue)
{
    free(pqueue->items);
}

bool IsFull(const Queue *pqueue, const int MAX_QUEUE)
{
    return pqueue->front == (pqueue->rear + 1) % (MAX_QUEUE + 1);
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

void EnQueue(Queue *pqueue, const Data item, const int MAX_QUEUE)
{
    if (IsFull(pqueue, MAX_QUEUE))
        exit(1);
    pqueue->items[pqueue->rear] = item;
    pqueue->rear = (pqueue->rear + 1) % (MAX_QUEUE + 1);
}

void DeQueue(Queue *pqueue, const int MAX_QUEUE)
{
    if (IsEmpty(pqueue))
        exit(1);
    pqueue->front = (pqueue->front + 1) % (MAX_QUEUE + 1);
}

bool IsOnlyOne(const Queue *pqueue, const int MAX_QUEUE)
{
    return pqueue->rear == (pqueue->front + 1) % (MAX_QUEUE + 1);
}

void PopAPointPencil(void)
{
    Queue queue;
    int n, k;
    Data* initialState;
    int i;
    scanf("%d %d\n", &n, &k);
    initialState = (Data *)malloc(sizeof(Data) * (k + 1));
    scanf("%s", initialState);
    InitQueue(&queue, initialState, k); free(initialState);

    for (i = 0; i < n; i++)
    {
        int option;
        scanf("%d", &option);
        switch(option)
        {
            case 0:
                if (IsEmpty(&queue))
                    break;
                printf("%c\n", Peek(&queue));
                break;
            case 1:
                if ( IsEmpty(&queue) || IsOnlyOne(&queue, k) )
                    break;
                DeQueue(&queue, k);
                break;
            case 2:
            {
                Data item;   
                scanf(" %c", &item);
                if (IsFull(&queue, k))
                    break;
                EnQueue(&queue, item, k);
                break;
            }
            default:
                exit(1);
        }
    }
    DeleteQueue(&queue);
}