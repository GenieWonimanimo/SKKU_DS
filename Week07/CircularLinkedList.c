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
    Node* tail; // tail node is last node
    int len;
} CircularList;

void InitList(CircularList* plist);
void InsertInitItem(CircularList* plist, Data item);
bool IsEmpty(CircularList* plist);
void InsertFisrt(CircularList* plist, Data item);
void InsertLast(CircularList* plist, Data item);
void InsertMiddle(CircularList* plist, int pos, Data item);
void RemoveInitItem(CircularList* plist);
void RemoveFirst(CircularList* plist);
void RemoveLast(CircularList* plist);
void RemoveMiddle(CircularList* plist, int pos);
void ClearList(CircularList* plist);

int main(void)
{

    return 0;
}

void InitList(CircularList* plist)
{
    plist->tail = NULL;
    plist->len = 0;
}

void InsertInitItem(CircularList* plist, Data item)
{
    // Create a new node.
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = newNode;

    plist->tail = newNode;
    plist->len++;
}

bool IsEmpty(CircularList* plist)
{
    return plist->len == 0;
}

void InsertFisrt(CircularList* plist, Data item)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, item);
    else
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = plist->tail->next;

        // Connect the back node to the new node
        plist->tail->next = newNode;
        plist->len++;
    }
}

void InsertLast(CircularList* plist, Data item)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, item);
    else
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = plist->tail->next;

        // Connect the back node to the new node
        plist->tail->next = newNode;
        plist->tail = newNode;
        plist->len++;
    }
}

void InsertMiddle(CircularList* plist, int pos, Data item)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, item);
    else
    {
        Node* cur, *newNode;
        cur = plist->tail;
        for (int i = 0; i < pos; i++)
            cur = cur->next;

        newNode = (Node *)malloc(sizeof(Node));
        newNode->item = item;
        newNode->next = cur->next;
        cur->next = newNode;
        plist->len++;
    }
}

void RemoveInitItem(CircularList* plist)
{
    if (IsEmpty(plist)) exit(1);

    if (plist->len == 1)
    {
        free(plist->tail);
        plist->len--;
        plist->tail = NULL;
    }
}

void RemoveFirst(CircularList* plist)
{
    if (plist->len == 1)
        RemoveInitItem(plist);
    else
    {
        Node* temp = plist->tail->next;
        plist->tail->next = temp->next;

        free(temp);
        plist->len--;
    }
}

void RemoveLast(CircularList* plist)
{
    if (plist->len == 1)
        RemoveInitItem(plist);
    else
    {
        Node* cur, *temp;
        int i;
        cur = plist->tail;
        for (i = 0; i < plist->len - 1; i++)
            cur = cur->next;
        temp = cur->next; // temp is now head->tail
        cur->next = temp->next;

        free(temp);
        plist->tail = cur;
        plist->len--;
    }
}

void RemoveMiddle(CircularList* plist, int pos)
{
    if (plist->len == 1)
        RemoveInitItem(plist);
    else
    {
        Node* cur, *temp;
        int i;
        cur = plist->tail;
        for (i = 0; i < pos; i++)
            cur = cur->next;
        temp = cur->next;
        cur->next = temp->next;

        free(temp);
        plist->len--; 
    }
}

void ClearList(CircularList* plist)
{
    while (plist->len > 0)
        RemoveFirst(plist);
}