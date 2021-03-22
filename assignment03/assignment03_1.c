#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {MOVE, ADD, ERASE} OPTION;
typedef char Data;

typedef struct _Node
{
    Data item;
    struct _Node* prev;
    struct _Node* next;
} Node;

typedef struct
{
    Node* head;
    Node* cursor;
    int len;
} DoubleLinkedList;

void InitList(DoubleLinkedList* plist);
bool IsEmpty(DoubleLinkedList* plist);
void MoveCursor(DoubleLinkedList* plist, char dir);
void InsertAtCursor(DoubleLinkedList* plist, Data item);
void RemoveLeftOfCursor(DoubleLinkedList* plist);
void PrintList(DoubleLinkedList* plist);
void ClearList(DoubleLinkedList* plist);

OPTION Option(void);
void SearchBar(void);

int main(void)
{
    SearchBar();
    return 0;
}


void InitList(DoubleLinkedList* plist)
{
    Node* dummy1, *dummy2;
    dummy1 = (Node *)malloc(sizeof(Node));
    dummy2 = (Node *)malloc(sizeof(Node));
    plist->cursor = (Node *)malloc(sizeof(Node));

    dummy1->prev = NULL;
    dummy1->next = plist->cursor;
    plist->cursor->prev = dummy1;
    plist->cursor->next = dummy2;
    dummy2->prev = plist->cursor;
    dummy2->next = NULL;

    plist->head = dummy1;
    plist->len = 0;
}

bool IsEmpty(DoubleLinkedList* plist)
{
    return plist->len == 0;
}

void MoveCursor(DoubleLinkedList* plist, char dir)
{
    if (dir == 'l')
    {
        Node* temp = plist->cursor->prev;
        if (plist->head->next == plist->cursor) // is cursor is left end?
            return;
        plist->cursor->prev = temp->prev;
        temp->prev->next = plist->cursor;
        plist->cursor->next->prev = temp;
        temp->next = plist->cursor->next;
        temp->prev = plist->cursor;
        plist->cursor->next = temp;
    }
    else // dir == 'r'
    {
        Node* temp = plist->cursor->next;
        if (plist->cursor->next->next == NULL) // is cursor is right end?
            return;
        plist->cursor->next = temp->next;
        temp->next->prev = plist->cursor;
        plist->cursor->prev->next = temp;
        temp->prev = plist->cursor->prev;
        temp->next = plist->cursor;
        plist->cursor->prev = temp;
    }
}

void InsertAtCursor(DoubleLinkedList* plist, Data item)
{
    Node* newNode;
    int i;

    // Create a new node
    newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;

    newNode->prev = plist->cursor->prev;
    plist->cursor->prev->next = newNode;
    plist->cursor->prev = newNode;
    newNode->next = plist->cursor;

    plist->len++;
}

void RemoveLeftOfCursor(DoubleLinkedList* plist)
{
    Node* temp;
    int i;
    if (IsEmpty(plist) || plist->head->next == plist->cursor)
        exit(1);

    temp = plist->cursor->prev;
    plist->cursor->prev->prev->next = plist->cursor;
    plist->cursor->prev = plist->cursor->prev->prev;

    // Remove left of the cursor
    free(temp);
    plist->len--;
}

void PrintList(DoubleLinkedList* plist)
{
    Node* cur;
    for (cur = plist->head->next; cur->next != NULL; cur = cur->next)
    {
        if (cur == plist->cursor)
            continue;
        printf("%c", cur->item);
    }
}

void ClearList(DoubleLinkedList* plist)
{
    while (plist->head->next != NULL)
    {
        Node* temp = plist->head;
        plist->head = plist->head->next;
        free(temp);
    }
    free(plist->head);
}

OPTION Option(void)
{
    char option[6];
    scanf("%s", option);
    if (!strcmp(option, "move"))
        return MOVE;
    else if (!strcmp(option, "add"))
        return ADD;
    else if (!strcmp(option, "erase"))
        return ERASE;
    else
        exit(3);
}

void SearchBar(void)
{
    DoubleLinkedList list;
    int n;
    int i;

    InitList(&list);
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        switch (Option())
        {
            case MOVE:
            {
                char dir;
                scanf(" %c", &dir);
                MoveCursor(&list, dir);
                break;
            }
            case ADD:
            {
                Data item;
                scanf(" %c", &item);
                item = (item == '_') ? ' ' : item;
                InsertAtCursor(&list, item);
                break;
            }
            case ERASE:
                if (IsEmpty(&list) || list.head->next == list.cursor) 
                    break;
                RemoveLeftOfCursor(&list);
                break;
            default: exit(4);
        }
    }
    PrintList(&list);
    ClearList(&list);
}