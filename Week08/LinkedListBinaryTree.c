#include <stdio.h>
#include <stdlib.h>

typedef int BData;

typedef struct _bTreeNode
{
    BData item;
    struct _bTreeNode* lect_child;
    struct _bTreeNode* right_child;
} BTreeNode;

// create a new node.
BTreeNode* CreateNode(BData item);
// destroy a node.
void DestroyNode(BTreeNode* node);

// connect the root to a left-side node.
void CreateLeftSubTree(BTreeNode* root, BTreeNode* left);
// connect the root to a right-side node.
void CreateRightSubTree(BTreeNode* root, BTreeNode* right);

// traverse a tree
void Inorder(BTreeNode* root);
void Preorder(BTreeNode* root);
void Postorder(BTreeNode* root);
void Levelorder(BTreeNode* root);

// total number of nodes
int Nodes(BTreeNode* node);
// height of binary tree
int Height(BTreeNode* node)
{
    int r = 0, l = 0;
    if (node->right_child != NULL)
        r = Height(node->right_child);
    if (node->lect_child != NULL)
        l = Height(node->lect_child);

    return 1 + max(r, l);
}

int main(void)
{
    BTreeNode* node1 = CreateNode(1);
    BTreeNode* node2 = CreateNode(2);
    BTreeNode* node3 = CreateNode(3);
    BTreeNode* node4 = CreateNode(4);
    BTreeNode* node5 = CreateNode(5);
    BTreeNode* node6 = CreateNode(6);

    CreateLeftSubTree(node1, node2);
    CreateRightSubTree(node1, node3);

    CreateLeftSubTree(node2, node4);
    CreateRightSubTree(node2, node5);
    CreateLeftSubTree(node3, node6);

    DestroyNode(node1);
    DestroyNode(node2);
    DestroyNode(node3);
    DestroyNode(node4);
    DestroyNode(node5);
    DestroyNode(node6);
    return 0;
}

// create a new node.
BTreeNode* CreateNode(BData item)
{
    BTreeNode* node = (BTreeNode *)malloc(sizeof(BTreeNode));
    node->item = item;
    node->lect_child = NULL;
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
    if (root->lect_child != NULL)
        exit(1);
    
    root->lect_child = left;
}
// connect the root to a right-side node.
void CreateRightSubTree(BTreeNode* root, BTreeNode* right)
{
    if (root->right_child != NULL)
        exit(1);

    root->right_child = right;
}

// traverse a tree
void Inorder(BTreeNode* root);
void Preorder(BTreeNode* root);
void Postorder(BTreeNode* root);
void Levelorder(BTreeNode* root);

int Nodes(BTreeNode* node)
{
    int r = 0, l = 0;
    if (node->right_child != NULL)
        r = Nodes(node->right_child);
    if (node->lect_child != NULL)
        l = Nodes(node->lect_child);

    return l + r + 1;
}