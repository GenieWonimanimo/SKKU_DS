#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

enum {INSERT = 'I', DELETE = 'D', COUNT = 'C', RANGECOUNT = 'R', TOP = 'T'};
typedef struct _BSTNode
{
    int grade; // lowest is best
    int num; // the number of diamonds
    int left_num;
    int right_num;
    struct _BSTNode* left_child;
    struct _BSTNode* right_child;
} BSTNode;

typedef struct _SNode
{
    BSTNode* cur;
    struct _SNode* next;
} SNode;
typedef struct
{
    SNode* top; // actually, it is same as head.
} DStack;

// Make stack empty.
void InitStack(DStack *pstack);
// Check whehter stack is empty
bool IsEmpty(DStack *pstack);

// Read the item at the top
BSTNode* Peek(DStack *pstack);
// Insert an item at the top
void Push(DStack *pstack, BSTNode* cur);
// Remove the item at the top
void Pop(DStack *pstack);

// Create a new node
BSTNode* CreateNode(int grade, int num);
// Destroy a node
void DestroyNode(BSTNode* node);

// Insert an item to BST (Iterative)
// Add m diamonds of grade n to the inventory
void Insert(BSTNode* root, int grade, int num);
// Remove an item from BST
// Delete m diamonds of grade n from the inventory
void Delete(BSTNode* root, int grade, int num);
// Search an item in BST (Iterative)
BSTNode* Search(BSTNode* root, int grade);
// Check how many grade n diamonds are left in stock
int Count(BSTNode* root, int grade);
// Check how many diamonds are in stock with grades between n and m(both inclusive)
int RangeCount(BSTNode* root, int grade1, int grade2);
// Get the grade of the n-th highest valuable diamond
// Iterative inorder using stack
int Top(BSTNode* root, int n);
// Clear a tree
void ClearTree(BSTNode* root);

int main(void)
{
    BSTNode* inventory = CreateNode(-1, -1); // Initial state of tree
    int N;
    scanf(" %d", &N);
    for (int i = 0; i < N; i++)
    {
        char option;
        int n, m;
        scanf(" %c", &option);
        switch (option)
        {
            case INSERT:
                scanf(" %d %d", &n, &m);
                Insert(inventory, n, m);
                break;
            case DELETE:
                scanf(" %d %d", &n, &m);
                Delete(inventory, n, m);
                break;
            case COUNT:
                scanf(" %d", &n);
                printf("%d\n", Count(inventory, n));
                break;
            case RANGECOUNT:
                scanf(" %d %d", &n, &m);
                printf("%d\n", RangeCount(inventory, n, m));
                break;
            case TOP:
                scanf(" %d", &n);
                printf("%d\n", Top(inventory, n));
                break;
            default:
                exit(1);
        }
    }
    ClearTree(inventory);
    return 0;
}

// Make stack empty.
void InitStack(DStack *pstack)
{
    pstack->top = NULL;
}
// Check whehter stack is empty
bool IsEmpty(DStack *pstack)
{
    return pstack->top == NULL;
}
// Read the item at the top
BSTNode* Peek(DStack *pstack)
{
    if (IsEmpty(pstack))
        exit(2);
    return pstack->top->cur;
}
// Insert an item at the top
void Push(DStack *pstack, BSTNode* cur)
{
    SNode* newNode = (SNode *)malloc(sizeof(SNode));
    newNode->cur = cur;
    newNode->next = pstack->top;
    pstack->top = newNode;
}
// Remove the item at the top
void Pop(DStack *pstack)
{
    SNode* temp;
    if (IsEmpty(pstack)) exit(3);

    temp = pstack->top;
    pstack->top = pstack->top->next;
}

// Create a new node
BSTNode* CreateNode(int grade, int num)
{
    BSTNode* node = (BSTNode *)malloc(sizeof(BSTNode));
    node->grade = grade;
    node->num = num;
    node->left_num = 0;
    node->right_num = 0;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
// Destroy a node
void DestroyNode(BSTNode* node)
{
    free(node);
}

// Insert an item to BST (Iterative)
void Insert(BSTNode* root, int grade, int num)
{
    BSTNode* cur = root;
    if (cur->grade == -1) // empty inventory
    {
        cur->grade = grade;
        cur->num = num;
    }
    else
    {
        while (cur != NULL)
        {    
            // if grade is already exist, add the num of diamonds
            if (cur->grade == grade)
            {
                cur->num += num;
                break;
            }
            else if (cur->grade > grade)
            {
                // Insert a new node for a left child.
                if (cur->left_child == NULL)
                {
                    cur->left_child = CreateNode(grade, num);
                    cur->left_num += num;
                    break;
                }
                else
                {
                    cur->left_num += num;
                    cur = cur->left_child;
                }
            }
            else
            {
                // Insert a new node for a right child.
                if (cur->right_child == NULL)
                {
                    cur->right_child = CreateNode(grade, num);
                    cur->right_num += num;
                    break;
                }   
                else
                {
                    cur->right_num += num;
                    cur = cur->right_child;
                }
            }
        }
    } 
}
// Remove an item from BST
void Delete(BSTNode* root, int grade, int num)
{
    BSTNode* cur = Search(root, grade), *parent = NULL;
    BSTNode* org = cur;
    if (root->grade == -1) // empty inventory
        return;
    if (cur == NULL) // grade doesn't exist
        return;
    else // diamond is exist
    {
        // Find the current node and its parent node and update left/right num
        cur = root;
        while (cur != NULL && cur->grade != grade) // end when cur == NULL || cur->key == key
        {
            parent = cur;
            if (cur->grade > grade)
            {
                cur->left_num -= (org->num >= num) ? num : org->num;
                cur = cur->left_child;
            }
            else
            {
                cur->right_num -= (org->num >= num) ? num : org->num;
                cur = cur->right_child;
            }
        }
        if (cur->num > num)
        {
            cur->num -= num;
            return;
        }
        if (cur->left_child == NULL && cur->right_child == NULL)
        {
            if (parent != NULL)
            {
                // Remove the current node depending on its position
                if (parent->left_child == cur)
                    parent->left_child = NULL;
                else
                    parent->right_child = NULL;
            }
            else // There is only one node in the tree
            {
                // cur is root node
                cur->grade = -1;
                cur->num = -1;
                return;
            }
        }
        else if (cur->left_child == NULL || cur->right_child == NULL)
        {
            BSTNode* child;
            // Replace a node with its child node
            if (cur->left_child != NULL)
                child = cur->left_child;
            else
                child = cur->right_child;
            
            // Replace the child node of its parent node
            if (parent != NULL)
            {
                if (parent->left_child == cur)
                    parent->left_child = child;
                else
                    parent->right_child = child;
            }
            else // parent == NULL
            {
                // cur is root node
                cur->grade = child->grade;
                cur->num = child->num;
                cur->left_child = child->left_child;
                cur->right_child = child->right_child;
                cur = child;
            }
        }
        else // cur->left_child != NULL && cur->right_child != NULL
        {
            BSTNode* succ_parent = cur, *succ = cur->right_child;
            // Find the successor (left-most node of the current node)
            while (succ->left_child != NULL)
            {
                succ_parent = succ;
                succ = succ->left_child;
            }

            // If the successor has a child, update its the child node
            if (succ_parent->right_child == succ) // cur->right_child doesn't have left node
                succ_parent->right_child = succ->right_child;
            else
                succ_parent->left_child = succ->right_child;

            cur->grade = succ->grade;
            cur->num = succ->num;
            cur = succ; // Remove the successor
        }
        DestroyNode(cur);
    }
}
// Search an item in BST (Iterative)
BSTNode* Search(BSTNode* root, int grade)
{
    BSTNode* cur = root;
    while (cur != NULL)
    {
        if (cur->grade == grade) break;
        else if (cur->grade > grade)
            cur = cur->left_child;
        else
            cur = cur->right_child;
    }
    // if cant find, return NULL
    return cur;
}
// Check how many grade n diamonds are left in stock
int Count(BSTNode* root, int grade)
{
    BSTNode* node = Search(root, grade);
    if (node == NULL) // cant find
        return 0;
    else
        return node->num;
}
// Check how many diamonds are in stock with grades between n and m(both inclusive)
int RangeCount(BSTNode* root, int grade1, int grade2)
{
    int lt1 = 0;
    int lt2 = 0;
    BSTNode* cur = root;
    int cur1Num = 0;
    int minDiff = 2100000000;
    bool grade1Found = false;
    while (cur != NULL)
    {
        int diff;
        if (cur->grade >= grade1)
        {
            diff = cur->grade - grade1;
            if (diff < minDiff)
            {
                minDiff = diff;
                cur1Num = cur->num;
            }
            if (cur->grade == grade1)
            {
                grade1Found = true;
                break;
            }
            cur = cur->left_child;
        }
        else // cur->grade < grade1
        {
            lt1 += cur->num + cur->left_num;
            cur = cur->right_child;
        }
    }

    cur = root;
    while (cur != NULL)
    {
        if (cur->grade <= grade2)
        {
            lt2 += cur->num + cur->left_num;
            if (cur->grade == grade2) break;
            cur = cur->right_child;
        }
        else // cur->grade > grade2
            cur = cur->left_child;
    }
    //printf("lt2: %d\nlt1: %d\n", lt2, lt1);
    //printf("cur1Num: %d\n", cur1Num);
    if (grade1Found)
        return lt2 - lt1 + cur1Num;
    else
        return lt2 - lt1;
}
// Get the grade of the n-th highest valuable diamond
// Iterative inorder using stack    
int Top(BSTNode* root, int n)
{
    BSTNode* cur = root;
    int cnt = 0;
    // Create an empty stack
    DStack stack;
    InitStack(&stack);
    if (root->grade == -1) return -1; // empty
    while (cur != NULL || !IsEmpty(&stack)) // break when cur == NULL && stack is empty
    {
        while (cur != NULL)
        {
            Push(&stack, cur);
            cur = cur->left_child;
        } // cur == NULL
        cur = Peek(&stack); Pop(&stack);
        cnt += cur->num;
        if (cnt >= n) // n-th highest valuable diamond is at cur->grade
            return cur->grade;
        cur = cur->right_child;
    }
    // number of all diamonds is less than n
    return -1;
}
// Clear a tree
void ClearTree(BSTNode* root)
{
    if (root != NULL)
    {
        ClearTree(root->left_child);
        ClearTree(root->right_child);
        DestroyNode(root);
    }
}

/*
18
I 51 5
I 16 6
I 4 7
I 15 3
I 43 10
I 35 4
I 28 11
I 64 20
I 62 9
I 69 1
I 89 30
*/