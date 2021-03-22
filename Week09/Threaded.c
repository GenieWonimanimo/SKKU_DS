/* 특성 정리
pre 의 첫번째는 root node -> pre 의 첫번째가 1이라면 inorder로 옮겼을 때 1 이전이 왼쪽 subtree 이후가 오른쪽 subtree
tree 의 leaves만 operand 를 갖고, 나머지는 operator 를 갖는다. -> operator 의 위치를 찾아내 left 와 right 를 구별
left_child 와 right_child 가 NULL 이면 operand(leaf node)

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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
BTreeNode* leftMost(BTreeNode* node);
void Inorder(BTreeNode* node);
void Preorder(BTreeNode* node);
void Postorder(BTreeNode* node);

// create a new node.
BTreeNode* CreateNode(BData item)
{
    BTreeNode* node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->item = item;
    node->left_child = NULL;
    node->right_child = NULL;

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
    left->right_child = root;
    left->isThreaded = true;
}
// connect the root to a right-side node.
void CreateRightSubTree(BTreeNode* root, BTreeNode* right)
{
    if (root->isThreaded)
    {
        right->right_child = root->right_child;
        right->isThreaded = true;
        root->right_child = right;
        root->isThreaded = false;
    }
    else // root->right_child == NULL
        root->right_child = right;
}

BTreeNode* leftMost(BTreeNode* node)
{
    if (node == NULL) return NULL;
    while (node->left_child != NULL)
        node = node->left_child;
    return node;
}

void Inorder(BTreeNode* node)
{
    BTreeNode* cur = leftMost(node);
    while(cur != NULL)
    {
        printf("%d ", cur->item);
        // If the node is a thread node, go to its inorder successor
        if (cur->isThreaded)
            cur = cur->right_child;
        else
            cur = leftMost(cur->right_child);
    }
}
void Preorder(BTreeNode* node)
{
    if (node != NULL)
    {
        printf("%d ", node->item);
        Preorder(node->left_child);
        if (node->isThreaded == false)
            Preorder(node->right_child);
    }
}
void Postorder(BTreeNode* node)
{
    if (node != NULL)
    {
        Postorder(node->left_child);
        if (node->isThreaded == false)
            Postorder(node->right_child);
        printf("%d ", node->item);
    }
}