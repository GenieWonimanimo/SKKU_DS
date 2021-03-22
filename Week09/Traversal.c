#include <stdio.h>
#include <stdlib.h>

typedef int BData;

typedef struct _bTreeNode
{
    BData item;
    struct _bTreeNode* left_child;
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
// total number of nodes
int Nodes(BTreeNode* node);
// height of binary tree
int Height(BTreeNode* node);

// traverse a tree
void Inorder(BTreeNode* root);
void Preorder(BTreeNode* root);
void Postorder(BTreeNode* root);
void Levelorder(BTreeNode* root);

// Make use of postorder traversal
int CalDirectorySize(BTreeNode* root);
int CalculateExpTree(BTreeNode* root);
BTreeNode* MakeExpTree(char* exp, int len);

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
}
// connect the root to a right-side node.
void CreateRightSubTree(BTreeNode* root, BTreeNode* right)
{
    if (root->right_child != NULL)
        exit(1);

    root->right_child = right;
}

// traverse a tree
/*
with recursive, there is a problem about efficiency.
Therefore, if you can, use queue instread of recursive.
*/
/*
Inorder Traversal(LCR)
left subtree -> center node -> right subtree
recursively each subtree
*/
void Inorder(BTreeNode* root)
{
    if (root != NULL)
    {
        Inorder(root->left_child);
        printf("%d ", root->item);
        Inorder(root->right_child);
    }
}
/*
Preorder Traversal(CLR)
center node -> left subtree -> right subtree
recursively each subtree
*/
void Preorder(BTreeNode* root)
{
    if (root != NULL)
    {
        printf("%d ", root->item);
        Preorder(root->left_child);
        Preorder(root->right_child);
    }
}
/*
Postorder Traversal(LRC)
left subtree -> right subtree -> center node
recursively each subtree
*/
void Postorder(BTreeNode* root)
{
    if (root != NULL)
    {
        Postorder(root->left_child);
        Postorder(root->right_child);
        printf("%d ", root->item);
    }
}
/*
for each level, visit node from the left to right dir
*/
void Levelorder(BTreeNode* root)
{
    // use queue
    /*
    Queue queue;
    if (root == NULL) return;

    InitQueue(&queue);
    EnQueue(&queue, root);
    while (!IsEmpty(&queue))
    {
        root = Peek(&queue);
        DeQueue(&queue);

        printf("%d ", root->item);
        if (root->left_child != NULL)
            EnQueue(&queue, root->left_child);
        if (root->right_child != NULL)
            EnQueue(&queue, root->right_child);
    }
    */
}

int Nodes(BTreeNode* node)
{
    int r = 0, l = 0;
    if (node->right_child != NULL)
        r = Nodes(node->right_child);
    if (node->left_child != NULL)
        l = Nodes(node->left_child);

    return l + r + 1;
}

int Height(BTreeNode* node)
{
    int r = 0, l = 0;
    if (node->right_child != NULL)
        r = Height(node->right_child);
    if (node->left_child != NULL)
        l = Height(node->left_child);

    return 1 + max(r, l);
}

int CalDirectorySize(BTreeNode* root)
{
    int left_size, right_size;
    if (root == NULL) return 0;
    else
    {
        left_size = CalDirectorySize(root->left_child);
        right_size = CalDirectorySize(root->right_child);
        return (root->item + left_size + right_size);
    }
}

/*
To build expression tree,
Infix -> Postfix -> Expression tree 
   (use stack)     
*/
int CalculateExpTree(BTreeNode* root)
{
    int op1, op2;
    if (root == NULL) return 0;
    if (root->left_child == NULL && root->right_child == NULL)
        return root->item;
    
    op1 = CalculateExpTree(root->left_child);
    op2 = CalculateExpTree(root->right_child);

    switch (root->item)
    {
        case '+': return op1 + op2;
        case '-': return op1 - op2;
        case '*': return op1 * op2;
        case '/': return op1 / op2;
    }
    return 0;
    
}

BTreeNode* MakeExpTree(char* exp, int len)
{
    // use stack
    /*
        Stack stack;
        BTreeNode* node, *right_node, *left_node;
        int i;

        InitStack(&stack);
        for (i = 0; i < len; i++)
        {
            if ('0' <= exp[i] && exp[i] <= '9')
                node = CreateNode(exp[i]);
            else
            {
                right_node = Peek(&stack); Pop(&stack);
                left_node = Peek(&stack); Pop(&stack);

                node = CreateNode(exp[i]);
                CreateRightSubtree(node, right_node);
                CreateLeftSubtree(node, left_node);
            }
            Push(&stack, node);     
        }
        return Peek(&stack);
    */
}