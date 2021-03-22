#include <stdio.h>
#include <stdbool.h>

#define MAX_LIST    100
typedef int Data;

typedef struct
{
    Data items[MAX_LIST];
    int len;
} ArrayList;


// Make a list empty.
void InitList(ArrayList* plist);
// Check whether the list is empty
bool IsEmpty(ArrayList* plist);
// Check whether the list is full
bool IsFull(ArrayList* plist);
// Insert an item at the k-th position
void InsertMiddle(ArrayList* plist, int pos, Data item);
// Remove an item at the k-th position
void RemoveMiddle(ArrayList* plist, int pos);
// Read an item at the k-th position
Data ReadItem(ArrayList* plist, int pos);
// Print each item in a list int sequence
void PrintList(ArrayList* plist);

int main(void)
{

    return 0;
}

void InitList(ArrayList* plist)
{
    plist->len = 0;
}

bool IsEmpty(ArrayList* plist)
{
    return plist->len == 0;
}

bool IsFull(ArrayList* plist)
{
    return plist->len == MAX_LIST;
}

void InsertMiddle(ArrayList* plist, int pos, Data item)
{
    int i;
    if (IsFull(plist) || pos < 0 || pos > plist->len) // 넣는거니까 비어있는 공간이 plist->len 도 괜찮다.
        exit(1);
    
    for (i = plist->len - 1; i >= pos; i--)
        plist->items[i + 1] = plist->items[i];
    plist->items[pos] = item;
    plist->len++;
}

void RemoveMiddle(ArrayList* plist, int pos)
{
    int i;
    if (IsEmpty(plist) || pos < 0 || pos >= plist->len) // 지우는 건데 plist->len 은 비어있어서 안된다.
        exit(1);

    for (i = pos; i < plist->len - 1; i++)
        plist->items[i] = plist->items[i + 1];
    plist->len--;
}

Data ReadItem(ArrayList* plist, int pos)
{
    if (IsEmpty(plist) || pos < 0 || pos >= plist->len)
        exit(1);

    return plist->items[pos];
}

void PrintList(ArrayList* plist)
{
    int i;
    for (i = 0; i < plist->len; i++)
        printf("%d\n", plist->items[i]);
}