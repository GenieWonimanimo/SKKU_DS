/*
pre 의 첫번째는 root node -> pre 의 첫번째가 1이라면 inorder로 옮겼을 때 1 이전이 왼쪽 subtree 이후가 오른쪽 subtree
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {LEFT, BETWEEN, RIGHT} POS;

typedef int BData;

typedef struct _bTreeNode
{
    BData item;
    struct _bTreeNode* left_child;
    struct _bTreeNode* right_child;
    bool isThreaded;
} BTreeNode;

BTreeNode* CreateNode(BData item);
void DestroyNode(BTreeNode* node);

void CreateLeftSubTree(BTreeNode* root, BTreeNode* left);
void CreateRightSubTree(BTreeNode* root, BTreeNode* right);

void Postorder(BTreeNode* node);

POS FindPos(BTreeNode* node, int* pinorder, int len, BData item);
BTreeNode* ConvInPreToPost(void);

int main(void)
{
    Postorder(ConvInPreToPost());
    return 0;
}
// create a new node.
BTreeNode* CreateNode(BData item)
{
    BTreeNode* node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->item = item;
    node->left_child = NULL;
    node->right_child = NULL;
    node->isThreaded = false;
    return node;
}
// destroy a node.
void DestroyNode(BTreeNode* node)
{
    free(node);
}
// connect the root to a left-side node.
void CreateLeftSubTree(BTreeNode* root, BTreeNode* left)
{
    if (root->left_child != NULL)
        exit(1);
    
    root->left_child = left;
    left->right_child = root; // make thread
    left->isThreaded = true;
}
// connect the root to a right-side node.
void CreateRightSubTree(BTreeNode* root, BTreeNode* right)
{
    if (root->isThreaded)
    {
        right->right_child = root->right_child; // change thread
        right->isThreaded = true;
        root->right_child = right;
        root->isThreaded = false;
    }
    else // root->right_child == NULL
        root->right_child = right;
}

void Postorder(BTreeNode* node) // LRC
{
    if (node != NULL)
    {
        Postorder(node->left_child);
        if (node->isThreaded == false) // not threaded
            Postorder(node->right_child); // not threaded 여도 null 이면 출력문 없음
        printf("%d ", node->item);
        DestroyNode(node);
    }
}

POS FindPos(BTreeNode* node, int* pinorder, int len, BData item)
{
    int nodeIdx = -1, ThreadIdx = -1, itemIdx = -1;
    int i;
    // get each index
    for (i = 0; i < len; i++)
    {
        if (pinorder[i] == item)
            itemIdx = i;
        else if (pinorder[i] == node->item)
            nodeIdx = i;
        else if (node->isThreaded && pinorder[i] == node->right_child->item)
            ThreadIdx = i;
    }
    // each idx must be different
    if (itemIdx < nodeIdx)
        return LEFT; // node that contains item is left of the parameter node in inorder
    else if (itemIdx < ThreadIdx || ThreadIdx == -1) // ThreadIdx == -1 cannot be changed with ->isThreaded == false because of subtree right of the root
        return BETWEEN; // node that contains item is between param node and node->thread
    else
        return RIGHT; // node that contains item is right of param node and node->thread
}

BTreeNode* ConvInPreToPost(void)
{
    int n;
    BTreeNode** nodesArr;
    BTreeNode* root;
    BTreeNode* cur;
    int* preorder, *inorder;
    int i;
    scanf("%d", &n);
    nodesArr = (BTreeNode **)malloc(sizeof(BTreeNode *) * n);
    preorder = (int *)malloc(sizeof(int) * n);
    inorder = (int *)malloc(sizeof(int) * n);
    for (i = 0; i < n; i++)
        scanf(" %d", &preorder[i]);
    for (i = 0; i < n; i++)
        scanf(" %d", &inorder[i]);
    for (i = 0; i < n; i++)
        nodesArr[i] = CreateNode(preorder[i]);
    cur = root = nodesArr[0];

    for (i = 1; i < n; i++)
    {
        switch (FindPos(cur, inorder, n, nodesArr[i]->item))
        {
            case LEFT:
                CreateLeftSubTree(cur, nodesArr[i]);
                cur = nodesArr[i];
                break;
            case BETWEEN:
                CreateRightSubTree(cur, nodesArr[i]);
                cur = nodesArr[i];
                break;
            case RIGHT:
                cur = cur->right_child; // go up via thread
                i--;
                break;
            default:
                exit(1);
        }
    }
    return root;
}

/*
1 2 3 4 5 6 7 8 9 10
3 6 5 7 4 2 1 9 8 10
res: 6 7 5 4 3 2 9 10 8 1

1 2 4 5 6 7 3 8 9 10
5 4 2 7 6 1 3 9 8 10
res: 5 4 7 6 2 9 10 8 3 1
*/