// bst animation
// https://visualgo.net/en/bst
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Decl___________________________________________________________________
typedef int Key;
typedef struct _BSTNode
{
    Key key;
    struct _BSTNode* left_child;
    struct _BSTNode* right_child;
} BSTNode;

// Create a new node
BSTNode* CreateNode(Key key);
// Destroy a node
void DestroyNode(BSTNode* node);

// Verify whether the tree is a binary search tree or not
bool Verify(BSTNode* root, int min, int max);
/*
// Search an item in BST (Recursive)
BSTNode* Search(BSTNode* root, Key key); 
*/
// Search an item in BST (Iterative)
BSTNode* Search(BSTNode* root, Key key);
/*
// Insert an item to BST (Recursive)
void Insert(BSTNode* root, Key key);
*/
// Insert an item to BST (Iterative)
void Insert(BSTNode* root, Key key);
// Remove an item from BST
void Remove(BSTNode* root, Key key);

// Traverse BST(the inorder traversal in a sorted list)
void Traverse(BSTNode* root);
// Clear a tree
void ClearTree(BSTNode* root);
// Decl__________________________________________________________________

// Def___________________________________________________________________

// Create a new node
BSTNode* CreateNode(Key key)
{
    BSTNode* node = (BSTNode *)malloc(sizeof(BSTNode));
    node->key = key;
    node->left_child = NULL;
    node->right_child = NULL;
    return node;
}
// Destroy a node
void DestroyNode(BSTNode* node)
{
    free(node);
}

// Verify whether the tree is a binary search tree or not
// Initialize the min and max as INT_MIN and INT_MAX (you can use this as constant)
// for 32 bits, -214783648 ~ 214783647
bool Verify(BSTNode* root, int min, int max)
{
    if (root != NULL)
    {
        // Return false if this node violates the min/max constraints
        if (root->key < min || root->key > max)
            return false;
        else
        {
            // Check the subtrees with the min/max constraints
            return Verify(root->left_child, min, root->key) && Verify(root->right_child, root->key, max);
        }
    }
    else
        return true; // an empty tree is BST
}
/*
// Search an item in BST(Recursive)
BSTNode* Search(BSTNode* root, Key key)
{
    if (root == NULL || root->key == key) return root;
    else if (root->key > key)
        return Search(root->left_child, key);
    else
        return Search(root->right_child, key);
}
*/
// Search an item in BST (Iterative)
BSTNode* Search(BSTNode* root, Key key)
{
    BSTNode* cur = root;
    while (cur != NULL)
    {
        if (cur->key == key) break;
        else if (cur->key > key)
            cur = cur->left_child;
        else
            cur = cur->right_child;
    }
    return cur; // cant find, return NULL
}
/*
// Insert an item to BST (Recursive)
void Insert(BSTNode* root, Key key)
{
    if (root->key == key) exit(1);
    else if (root->key > key)
    {
        // Insert a new node for a left child.
        if (root->left_child == NULL)
            root->left_child = CreateNode(key);
        else
            Insert(root->left_child, key);
    }
    else
    {
        // Insert a new node for a right child
        if (root->right_child == NULL)
            root->right_child = CreateNode(key);
        else
            Insert(root->right_child, key);
    }
}
*/
// Insert an item to BST (Iterative)
void Insert(BSTNode* root, Key key)
{
    BSTNode* cur = root;
    if (cur->key == -1) // empty
        cur->key = key;
    else
    {
        while (cur != NULL)
        {
            if (cur->key == key) exit(1);
            else if (cur->key > key)
            {
                // Insert a new node for a left child.
                if (cur->left_child == NULL)
                {
                    cur->left_child = CreateNode(key);
                    break;
                }
                else
                    cur = cur->left_child;
            }
            else
            {
                // Insert a new node for a right child.
                if (cur->right_child == NULL)
                {
                    cur->right_child = CreateNode(key);
                    break;
                }
                else
                    cur = cur->right_child;
            }
        }
    }
}
// Remove an item from BST
void Remove(BSTNode* root, Key key)
{
    BSTNode* cur = root, *parent = NULL;
    if (cur->key == -1) // empty
        return;

    // Find the current node and its parent node
    while (cur != NULL && cur->key != key) // end when cur == NULL || cur->key == key
    {
        parent = cur; // Update the parent node
        if (cur->key > key)
            cur = cur->left_child;
        else
            cur = cur->right_child;
    }

    if (cur == NULL) return; // cant find
    else if (cur->left_child == NULL && cur->right_child == NULL)
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
            cur->key = 1; // The current node is the root
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
            cur->key = child->key;
            cur->left_child = child->left_child;
            cur->right_child = child->right_child;
            cur = child;
        }
        DestroyNode(cur);
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

        cur->key = succ->key;
        cur = succ; // Remove the successor
        DestroyNode(cur);
    }
}

// Traverse BST(the inorder traversal in a sorted list)
void Traverse(BSTNode* root)
{
    if (root != NULL)
    {
        Traverse(root->left_child);
        printf("%d ", root->key);
        Traverse(root->right_child);
    }
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

// Def___________________________________________________________________

/*
Time complexity
            Average     Worst case
Searching   O(logn)     O(n)
Insertion   O(logn)     O(n)
Deletion    O(logn)     O(n)
*/