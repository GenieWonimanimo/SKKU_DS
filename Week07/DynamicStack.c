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
    Node* top; // actually, it is same as head.
} DStack;

// Make stack empty.
void InitStack(DStack *pstack);
// Check whehter stack is empty
bool IsEmpty(DStack *pstack);

// Read the item at the top
Data Peek(DStack *pstack);
// Insert an item at the top
void Push(DStack *pstack, Data item);
// Remove the item at the top
void Pop(DStack *pstack);

int main(void)
{

    return 0;
}


void InitStack(DStack *pstack)
{
    pstack->top = NULL;
}

bool IsEmpty(DStack *pstack)
{
    pstack->top == NULL;
}

Data Peek(DStack *pstack)
{
    if (IsEmpty(pstack))
        exit(1);
    return pstack->top->item;
}

void Push(DStack *pstack, Data item)
{
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = pstack->top;
    pstack->top = newNode;
}

void Pop(DStack *pstack)
{
    Node* temp;
    if (IsEmpty(pstack)) exit(1);

    temp = pstack->top;
    pstack->top = pstack->top->next;
    free(temp);
}