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
    Node* head;
    int len;
} LinkedList;

// Make a list empty.
void InitList(LinkedList* plist);
// Check whether the list is empty. In here, no isfull
bool IsEmpty(LinkedList* plist);
// Insert an item at the k-th position.
void InsertMiddle(LinkedList* plist, int pos, Data item);
// Remove an item at the k-th position
void RemoveMiddle(LinkedList* plist, int pos);
// Read an item at the k-th position
Data ReadItem(LinkedList* plist, int pos);
// Print each item in a list in sequence
void PrintList(LinkedList* plist);
// Remove all nodes in a list in sequence.
void ClearList(LinkedList* plist);
LinkedList* Concatenate(LinkedList* plist1, LinkedList* plist2);
void Reverse(LinkedList* plist);

int main(void)
{

    return 0;
}   


void InitList(LinkedList* plist)
{
    // Create a dummy node
    plist->head = (Node *)malloc(sizeof(Node)); // head node °¡ dummy node
    plist->head->next = NULL;
    plist->len = 0;
}

bool IsEmpty(LinkedList* plist)
{
    return plist->len == 0;
}

void InsertMiddle(LinkedList* plist, int pos, Data item)
{
    Node* cur, *newNode;
    int i;
    if (pos < 0 || pos > plist->len)
        exit(1);
    // Create a new node
    newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    // Move the cur pointer to the (k - 1) th position
    cur = plist->head;
    for (i = 0; i < pos; i++)
        cur = cur->next;
    
    // Insert the new node to the k-th position
    newNode->next = cur->next;
    cur->next = newNode;
    plist->len++;
}

void RemoveMiddle(LinkedList* plist, int pos)
{
    Node* cur, * temp;
    int i;
    if (IsEmpty(plist) || pos < 0 || pos >= plist->len)
        exit(1);
    cur = plist->head;
    for (i = 0; i < pos; i++)
        cur = cur->next;
    
    // Remove the node to the k-th position
    temp = cur->next;
    cur->next = cur->next->next;
    plist->len--;
    free(temp);
}

Data ReadItem(LinkedList* plist, int pos)
{
    Node* cur;
    int i;
    if (IsEmpty(plist) || pos < 0 || pos >= plist->len)
        exit(1);

    // Move the cur pointer to the k-th position
    cur = plist->head->next;
    for (i = 0; i < pos; i++)
        cur = cur->next;

    return cur->item;
}

void PrintList(LinkedList* plist)
{
    Node* cur;
    for (cur = plist->head->next; cur != NULL; cur = cur->next)
        printf("%d\n", cur->item);
}

void ClearList(LinkedList* plist)
{
    while (plist->head->next != NULL)
        RemoveMiddle(plist, 0);
    free(plist->head);
}

LinkedList* Concatenate(LinkedList* plist1, LinkedList* plist2)
{
    if (plist1->head->next == NULL) return plist2;
    else if (plist2->head->next == NULL) return plist1;
    else
    {
        // Move the current pointer to the last position
        Node* cur = plist1->head->next;
        while (cur->next != NULL)
            cur = cur->next;
        // Link the current pointer to the second list
        cur->next = plist2->head->next;
        // Remove the dummy node from the second list
        free(plist2->head);
        return plist1;
    }
}

void Reverse(LinkedList* plist)
{
    Node* prev = NULL, *cur = NULL;
    Node *next = plist->head->next;

    while (next != NULL)
    {
        // Set the prev, cur, and next nodes.
        prev = cur;
        cur = next;
        next = next->next;
        // Change the link of the cur node.
        cur->next = prev;
    }
    // Connect the dummy node to the cur node.
    plist->head->next = cur;
}