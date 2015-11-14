// C program to demonstrate delete operation in binary search tree
// http://geeksquiz.com/binary-search-tree-set-2-delete/
#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node *left, *right;
};

// A utility function to create a new BST node
struct node *newNode(int item)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

// A utility function to do inorder traversal of BST
void inorder(struct node *root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

/*
An utility function to do key searching of BST.
Return the addr of the key node, or NULL if key not found.
*/
struct node *search(struct node *node, int number_to_search)
{
    if (node == NULL)
        return NULL;

    if (number_to_search == node->key)
        return node;

    if (number_to_search > node->key)
        return search(node->right, number_to_search);
    else
        return search(node->left, number_to_search);
}

/* A utility function to insert a new node with given key in BST */
struct node *insert(struct node *node, int key)
{
    /* If the tree is empty, return a new node */
    if (node == NULL)
        return newNode(key);

    /* Otherwise, recur down the tree */
    if (key < node->key)
        node->left = insert(node->left, key);
    else
        node->right = insert(node->right, key);

    /* return the (unchanged) node pointer */
    return node;
}

/* Given a non-empty binary search tree, return the node with minimum
key value found in that tree. Note that the entire tree does not
need to be searched. */
struct node *minValueNode(struct node *node)
{
    struct node *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

/* Given a binary search tree and a key, this function deletes the key
and returns the new root */
struct node *deleteNode(struct node *root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // If the key to be deleted is smaller than the root's key,
    // then it lies in left subtree
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in right subtree
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // if key is same as root's key, then This is the node
    // to be deleted
    else {
        // node with only one child or no child
        if (root->left == NULL) {
            struct node *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node *temp = root->left;
            free(root);
            return temp;
        }

        // node with two children: Get the inorder successor (smallest
        // in the right subtree)
        struct node *temp = minValueNode(root->right);

        // Copy the inorder successor's content to this node
        root->key = temp->key;

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

/*An utility function to copy a BST and returns the root addr.*/
struct node *copy_BST(struct node *curr)
{
    if (curr == NULL)
        return NULL;

    struct node *tmp = newNode(curr->key);
    tmp->left = copy_BST(curr->left);
    tmp->right = copy_BST(curr->right);

    return tmp;
}

/*An utility function that returns true when two BST are the same.*/
bool verify(struct node *root1, struct node *root2)
{
    if (root1 == NULL || root2 == NULL)
        return root1 == root2;

    if (root1 != NULL && root2 != NULL) {
        if (root1->key == root2->key)
            return verify(root1->left, root2->left) &&
                   verify(root1->right, root2->right);
    }

    return false;
}

// Driver Program to test above functions
int main()
{
    /*
        Let us create following BST
               50
            /	  \
           30	  70
           / \   / \
          20 40 60 80
    */
    struct node *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the given tree \n");
    inorder(root);

    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    struct node *root2 = copy_BST(root);
    printf("\n\nVerify %s\n", verify(root, root2) == true ? "true" : "false");

    root = deleteNode(root, 80);

    printf("\n\nVerify %s\n\n", verify(root, root2) == true ? "true" : "false");

    if (search(root, 50) == NULL)
        printf("50 is not in the tree\n");
    else
        printf("50 is in the tree\n");

    if (search(root, 40) == NULL)
        printf("40 is not in the tree\n");
    else
        printf("40 is in the tree\n");

    return 0;
}
