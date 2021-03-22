#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int MAX;
typedef enum {ALLOC, FREE} OPTION;

typedef int Data;
typedef struct _Node
{
    Data address;
    int len;
    struct _Node* next;
} Node;

typedef struct
{
    Node* head;
    int len;
} LinkedList;

void InitList(LinkedList* plist);
bool IsEmpty(LinkedList* plist);
void InsertMiddle(LinkedList* plist, int pos, Data paddress, int plen);
void RemoveMiddle(LinkedList* plist, int pos);
void ClearList(LinkedList* plist);

OPTION Option(void);
int Alloc(LinkedList* plist, int plen);
void Free(LinkedList* plist, int paddress, int plen);
void MemManage(void);

int main(void)
{
    MemManage();
    return 0;
}   


void InitList(LinkedList* plist)
{
    Node* first = (Node *)malloc(sizeof(Node));
    Node* last = (Node *)malloc(sizeof(Node));
    plist->head = (Node *)malloc(sizeof(Node));

    first->address = 0; first->len = 0;
    last->address = MAX; last->len = 0;
    plist->head->next = first;
    first->next = last;
    last->next = NULL;
    plist->len = 2;
}

bool IsEmpty(LinkedList* plist)
{
    return plist->len == 0;
}

void InsertMiddle(LinkedList* plist, int pos, Data paddress, int plen)
{
    Node* cur, *newNode;
    int i;
    if (pos < 0 || pos > plist->len)
        exit(1);
    // Create a new node
    newNode = (Node *)malloc(sizeof(Node));
    newNode->address = paddress;
    newNode->len = plen;
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

void ClearList(LinkedList* plist)
{
    while (plist->head->next != NULL)
        RemoveMiddle(plist, 0);
    free(plist->head);
}

OPTION Option(void)
{
    char option[6];
    scanf("%s", option);
    if (!strcmp(option, "alloc"))
        return ALLOC;
    else if (!strcmp(option, "free"))
        return FREE;
    else
        exit(1);
}

int Alloc(LinkedList* plist, int plen)
{
    Node* cur = plist->head;
    Node* optimal = plist->head->next;
    int emptySpace = MAX + 1;
    int optimalPos;
    bool canEnter = false;
    int i;

    for (i = 0; i < plist->len - 1; i++)
    {
        int emptyLen;
        cur = cur->next;
        emptyLen = cur->next->address - (cur->address + cur->len);
        if (plen <= emptyLen && emptyLen < emptySpace)
        {
            canEnter = true;
            optimal = cur;
            emptySpace = emptyLen;
            optimalPos = i + 1;
        }
    }

    if (canEnter)
    {
        InsertMiddle(plist, optimalPos, optimal->address + optimal->len, plen);
        return optimal->address + optimal->len;
    }
    else
        return -1;
}

    

void Free(LinkedList* plist, int paddress, int plen)
{
    Node* cur = plist->head;
    int i;
    for (i = 0; i < plist->len; i++)
    {
        cur = cur->next;
        if (cur->address == paddress && cur->len == plen) break;
    }
    RemoveMiddle(plist, i);
}

void MemManage(void)
{
    LinkedList list;
    int N;
    int i;
    scanf("%d %d", &MAX, &N);
    
    InitList(&list);
    for (i = 0; i < N; i++)
    {
        switch (Option())
        {
            case ALLOC:
            {
                int len; scanf(" %d", &len);
                printf("%d\n", Alloc(&list, len));
                break;
            }
            case FREE:
            {
                int addr, len;
                scanf(" %d %d", &addr, &len);
                Free(&list, addr, len);
                break;
            }
            default:
                exit(1);
        }
    }
    ClearList(&list);
}