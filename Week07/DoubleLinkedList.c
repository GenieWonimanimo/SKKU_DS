#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;
typedef struct _Node
{
    Data item;
    struct _Node* prev;
    struct _Node* next;
} Node;

typedef struct
{
    Node* head;
    int len;
} DoubleLinkedList;

void InitList(DoubleLinkedList* plist);
bool IsEmpty(DoubleLinkedList* plist);
void InsertMiddle(DoubleLinkedList* plist, int pos, Data item);
void RemoveMiddle(DoubleLinkedList* plist, int pos);

int main(void)
{

    return 0;
}

void InitList(DoubleLinkedList* plist)
{
    Node* dummy1, *dummy2;
    dummy1 = (Node *)malloc(sizeof(Node));
    dummy2 = (Node *)malloc(sizeof(Node));

    dummy1->prev = NULL;
    dummy1->next = dummy2;
    dummy2->prev = dummy1;
    dummy2->next = NULL;

    plist->head = dummy1;
    plist->len = 0;
}

bool IsEmpty(DoubleLinkedList* plist)
{
    return plist->len == 0;
}

void InsertMiddle(DoubleLinkedList* plist, int pos, Data item)
{
    Node* cur, *newNode;
    int i;

    // Create a new node
    newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;

    cur = plist->head;
    for (i = 0; i < pos; i++)
        cur = cur->next;

    // Insert the new node to the k-th position
    newNode->prev = cur;
    newNode->next = cur->next;
    cur->next->prev = newNode;
    cur->next = newNode;
    plist->len++;
}

void RemoveMiddle(DoubleLinkedList* plist, int pos)
{
    Node* cur, *temp;
    int i;
    if (IsEmpty(plist) || pos < 0 || pos >= plist->len)
        exit(1);

    // Move the cur pointer to the (k - 1)th position
    cur = plist->head;
    for (i = 0; i < pos; i++)
        cur = cur->next;

    // Connect adjacent nodes to remove the k-th node.
    temp = cur->next;
    temp->next->prev = cur;
    cur->next = temp->next;

    // Remove the node to the k-th position
    free(temp);
    plist->len--;
}