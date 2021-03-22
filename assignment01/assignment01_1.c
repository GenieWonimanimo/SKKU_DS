#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN   1000
typedef enum {false, true} bool;
typedef char Data;
typedef struct
{
    Data items[MAX_LEN];
    int top;
} Stack;

void InitStack(Stack *pstack);
bool IsFull(Stack *pstack);
bool IsEmpty(Stack *pstack);
Data Peek(Stack *pstack);
void Push(Stack *pstack, Data item);
void Pop(Stack *pstack);
int CalMountainHeight(char pMountain[], int len);

int main(void)
{
    char mountain[MAX_LEN];
    scanf("%s", mountain);
    printf("%d", CalMountainHeight(mountain, strlen(mountain)));
    return 0;
}

void InitStack(Stack *pstack)
{
    pstack->top = -1;
}

bool IsFull(Stack *pstack)
{
    return (pstack->top == MAX_LEN - 1);
}

bool IsEmpty(Stack *pstack)
{
    return (pstack->top == -1);
}

Data Peek(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->items[pstack->top];
}

void Push(Stack *pstack, Data item)
{
    if (IsFull(pstack))
        exit(1);
    pstack->items[++(pstack->top)] = item;
}

void Pop(Stack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    --(pstack->top);
}

int CalMountainHeight(char pMountain[], int len)
{
    Stack stack;
    int height = 0;
    int tmp = 0;
    int i;
    InitStack(&stack);
    for (i = 0; i < len; i++)
    {
        if (pMountain[i] == '/')
        {
            Push(&stack, pMountain[i]);
            tmp++;
            height = (tmp > height) ? tmp : height;
        }
        else
        {
            if (IsEmpty(&stack))
                return 0;
            else
            {
                Pop(&stack);
                tmp--;
            }
        }
    }
    if (IsEmpty(&stack))
        return height;
    else
        return 0;
}