#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Node
{
    int coef;
    int expon;
    struct _Node* next;
} Node;

typedef struct
{
    Node* tail;
    int len;
} Polynomial;

void InsertInitItem(Polynomial* plist, int coef, int expon);
bool IsEmpty(Polynomial* plist);
void InsertFisrt(Polynomial* plist, int coef, int expon);
void InsertLast(Polynomial* plist, int coef, int expon);
void InsertMiddle(Polynomial* plist, int pos,int coef, int expon);
void RemoveInitItem(Polynomial* plist);
void RemoveFirst(Polynomial* plist);
void RemoveLast(Polynomial* plist);
void RemoveMiddle(Polynomial* plist, int pos);
void ClearList(Polynomial* plist);

void InitPolynomial(Polynomial* plist);
void InputPolynomial(Polynomial* plist);
int SmallerLargestExpon(Polynomial* plist1, Polynomial* plist2, int largerExpon);
Polynomial* PlusPolynomial(Polynomial* plist1, Polynomial* plist2);
void PrintPolynomial(Polynomial* plist);

int main(void)
{
    Polynomial list1, list2;
    Polynomial* list3;
    InitPolynomial(&list1);
    InitPolynomial(&list2);
    printf("\n***Polynomial1***\n"); InputPolynomial(&list1);
    printf("\n***Polynomial2***\n"); InputPolynomial(&list2);
    PrintPolynomial(&list1);
    PrintPolynomial(&list2);

    list3 = PlusPolynomial(&list1, &list2);
    PrintPolynomial(list3);

    ClearList(&list1);
    ClearList(&list2);
    ClearList(list3);
    free(list3);
    return 0;
}

void InsertInitItem(Polynomial* plist, int coef, int expon)
{
    // Create a new node.
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->coef = coef;
    newNode->expon = expon;
    newNode->next = newNode;

    plist->tail = newNode;
    plist->len++;
}

bool IsEmpty(Polynomial* plist)
{
    return plist->len == 0;
}

void InsertFisrt(Polynomial* plist, int coef, int expon)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, coef, expon);
    else
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->coef = coef;
        newNode->expon = expon;
        newNode->next = plist->tail->next;

        // Connect the back node to the new node
        plist->tail->next = newNode;
        plist->len++;
    }
}

void InsertLast(Polynomial* plist, int coef, int expon)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, coef, expon);
    else
    {
        Node* newNode = (Node *)malloc(sizeof(Node));
        newNode->coef = coef;
        newNode->expon = expon;
        newNode->next = plist->tail->next;

        // Connect the back node to the new node
        plist->tail->next = newNode;
        plist->tail = newNode;
        plist->len++;
    }
}

void InsertMiddle(Polynomial* plist, int pos, int coef, int expon)
{
    if (IsEmpty(plist))
        InsertInitItem(plist, coef, expon);
    else
    {
        Node* cur, *newNode;
        cur = plist->tail;
        for (int i = 0; i < pos; i++)
            cur = cur->next;

        newNode = (Node *)malloc(sizeof(Node));
        newNode->coef = coef;
        newNode->expon = expon;
        newNode->next = cur->next;
        cur->next = newNode;
        plist->len++;
    }
}

void RemoveInitItem(Polynomial* plist)
{
    if (IsEmpty(plist)) exit(1);

    if (plist->len == 1)
    {
        free(plist->tail);
        plist->len--;
        plist->tail = NULL;
    }
}

void RemoveFirst(Polynomial* plist)
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

void RemoveLast(Polynomial* plist)
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
        temp = cur->next;
        cur->next = temp->next;

        free(temp);
        plist->tail = cur;
        plist->len--;
    }
}

void RemoveMiddle(Polynomial* plist, int pos)
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

void ClearList(Polynomial* plist)
{
    while (plist->len > 0)
        RemoveFirst(plist);
}

void InitPolynomial(Polynomial* plist)
{
    plist->tail = NULL;
    plist->len = 0;
}

void InputPolynomial(Polynomial* plist)
{
    char option;
    while (1)
    {
        int coef, expon;
        printf("more unary?(y / n): "); scanf(" %c", &option);
        if (option == 'n')
            break;
        printf("coef: "); scanf(" %d", &coef); 
        printf("expon: "); scanf(" %d", &expon);
        InsertLast(plist, coef, expon);
    }
}

int SmallerLargestExpon(Polynomial* plist1, Polynomial* plist2, int largerExpon)
{
    Node* cur;
    int smallerLargest = -1;
    int i;
    cur = plist1->tail;
    for (i = 0; i < plist1->len; i++)
    {
        cur = cur->next;
        smallerLargest = (largerExpon > cur->expon && cur->expon > smallerLargest) ? cur->expon : smallerLargest;
    }
    cur = plist2->tail;
    for (i = 0; i < plist2->len; i++)
    {
        cur = cur->next;
        smallerLargest = (largerExpon > cur->expon && cur->expon > smallerLargest) ? cur->expon : smallerLargest;        
    }

    return smallerLargest;
}

Polynomial* PlusPolynomial(Polynomial* plist1, Polynomial* plist2)
{
    Polynomial *desList = (Polynomial *)malloc(sizeof(Polynomial));
    Node* cur;
    int expon = SmallerLargestExpon(plist1, plist2, 2147483647);
    InitPolynomial(desList);
    while (1)
    {
        int coef = 0;
        int i;

        cur = plist1->tail;
        for (i = 0; i < plist1->len; i++)
        {
            cur = cur->next;
            if (cur->expon == expon)
                coef += cur->coef;
        }
        cur = plist2->tail;
        for (i = 0; i < plist2->len; i++)
        {
            cur = cur->next;
            if (cur->expon == expon)
                coef += cur->coef;
        }
        InsertLast(desList, coef, expon);
        
        expon = SmallerLargestExpon(plist1, plist2, expon);
        if (expon == -1)
            break;
    }
    return desList;
}

void PrintPolynomial(Polynomial* plist)
{
    Node* cur = plist->tail;
    int i;
    for (i = 0; i < plist->len - 1; i++)
    {
        cur = cur->next;
        printf("%dx^%d + ", cur->coef, cur->expon);
    }
    cur = cur->next;
    printf("%dx^%d\n", cur->coef, cur->expon);
}