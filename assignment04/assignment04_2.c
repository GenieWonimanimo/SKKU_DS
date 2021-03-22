#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Tree start
typedef bool BData;
typedef struct _bTreeNode
{
    BData item;
    struct _bTreeNode* left_child;
    struct _bTreeNode* right_child;
} BTreeNode;

BTreeNode* CreateNode(BData item);
void DestroyNode(BTreeNode* node);

void CreateLeftSubTree(BTreeNode* root, BTreeNode* left);
void CreateRightSubTree(BTreeNode* root, BTreeNode* right);
void PrintShape(BTreeNode* root);
// Tree fin

// Queue start
typedef BTreeNode* QData;
typedef struct _Node
{
    QData item;
    struct _Node* next;
} Node;

typedef struct
{
    Node* front;
    Node* rear;
} DQueue;

void InitQueue(DQueue *pqueue);
bool IsEmpty(DQueue *pqueue);

QData Peek(DQueue *pqueue);
void EnQueue(DQueue *pqueue, QData item);
void DeQueue(DQueue *pqueue);
// Queue fin

void CreateLeftRight(BTreeNode* root, bool pis_down);
BTreeNode* ShapeOfFold(bool pis_down, int pnFolds);

int main(void)
{
    int nFolds;
    bool is_down;
    scanf("%d %d", &is_down, &nFolds); is_down = !is_down;
    PrintShape(ShapeOfFold(is_down, nFolds));
    return 0;
}

// Tree start
BTreeNode* CreateNode(BData item)
{
    BTreeNode* node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->item = item;
    node->left_child = NULL;
    node->right_child = NULL;

    return node;
}
void DestroyNode(BTreeNode* node)
{
    free(node);
}
void CreateLeftSubTree(BTreeNode* root, BTreeNode* left)
{
    if (root->left_child != NULL)
        exit(1);
    
    root->left_child = left;
}
void CreateRightSubTree(BTreeNode* root, BTreeNode* right)
{
    if (root->right_child != NULL)
        exit(2);

    root->right_child = right;
}
// Tree fin

// Queue start
void InitQueue(DQueue *pqueue)
{
    pqueue->front = pqueue->rear = NULL;
}
bool IsEmpty(DQueue *pqueue)
{
    return pqueue->front == NULL;
}
QData Peek(DQueue *pqueue)
{
    if (IsEmpty(pqueue)) exit(3);

    return pqueue->front->item;
}
void EnQueue(DQueue *pqueue, QData item)
{
    Node* newNode = (Node *)malloc(sizeof(Node));
    newNode->item = item;
    newNode->next = NULL;

    if (IsEmpty(pqueue))
        pqueue->front = pqueue->rear = newNode;
    else
    {
        pqueue->rear->next = newNode;
        pqueue->rear = newNode;
    }
}
void DeQueue(DQueue *pqueue)
{
    Node* temp;
    if (IsEmpty(pqueue)) exit(4);

    temp = pqueue->front;
    if (temp->next == NULL) // is there only one in queue?
        pqueue->front = pqueue->rear = NULL;
    else
        pqueue->front = temp->next;
}
// Queue fin

// depend on pis_down, Create Left/Right child node of root node.
void CreateLeftRight(BTreeNode* root, bool pis_down)
{
    BTreeNode* left = CreateNode(pis_down);
    BTreeNode* right = CreateNode(!pis_down);
    CreateLeftSubTree(root, left);
    CreateRightSubTree(root, right);
}

// use level order traversal, make a tree and return the root node.
BTreeNode* ShapeOfFold(bool pis_down, int pnFolds)
{
    BTreeNode* root = CreateNode(pis_down);
    DQueue queue;
    int i;
    InitQueue(&queue);
    EnQueue(&queue, root);
    
    for (i = 0; i < pnFolds - 1; i++) // from level 1 to level pnFolds - 1
    {
        int j;
        for (j = 0; j < pow(2, i); j++)
        {
            BTreeNode* parent = Peek(&queue); DeQueue(&queue);
            CreateLeftRight(parent, pis_down);
            EnQueue(&queue, parent->left_child); 
            EnQueue(&queue, parent->right_child);
        }
    }
    return root;
}

// if root->item == true -> 'V' else '^'
void PrintShape(BTreeNode* root)
{
    if (root != NULL)
    {
        PrintShape(root->left_child);
        printf("%c", (root->item) ? 'V' : '^');
        PrintShape(root->right_child);
        // free visited node
        DestroyNode(root);
    }
}