#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define DEBUG 1

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node;

/*
Clears the terminal screen.
*/
void clear_screen()
{
    printf("\033[2J");
}

/*
Print out the menu and return the first character in the input string.
*/
int welcome_msg()
{
    printf("\nPlease make a choice: \n");
    printf("(B)inary Search Tree.\n");
    printf("(T)reasure Hunter\n");
    printf("(E)xit\n");

    char command_prompt[1000];
    scanf("%s", command_prompt);

    return command_prompt[0];
}

/*
The parameter is the key to be assigned.

If a new node is successfully created, the return value will be a pointer to the
newly created node.
Also, the node will be initialized with the key passed in, and left and right
pointer to NULL.
*/
Node *create_node(int key)
{
    Node *new_node = malloc(sizeof(Node));
    assert(new_node != NULL);

    new_node->key = key;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

/*
The parameters are the pointer to the starting node, and the key to be searched.

If the key is found, the return value will be the pointer to that node.
Otherwise, the return value is NULL.
*/
Node *BST_search(Node *curr, int key)
{
    if (curr == NULL)
        return NULL;
    else if (curr->key == key)
        return curr;
    else {
        if (curr->key < key) // right subtree
            return BST_search(curr->right, key);
        else // left subtree
            return BST_search(curr->left, key);
    }
}

/*
The parameters are the pointer to the starting node, and the key to be inserted.

The key will be inserted according to the BST rule, and the BST_head pointer
will be returned.
*/
Node *BST_insert(Node *BST_head, int key)
{
    if (BST_head == NULL) // The first node!
        return create_node(key);

    if (BST_head->key < key) // go to right subtree
        BST_head->right = BST_insert(BST_head->right, key);
    else if (BST_head->key > key) // go to left subtree
        BST_head->left = BST_insert(BST_head->left, key);
    else { // duplicated key
        printf("The number %d already exists.\n\n", key);
        return BST_head;
    }

    return BST_head;
}

/*
Teh parameter is the pointer to the starting node.

Perform an inorder traversal on the given BST tree.

Notice: Need to an \n after calling BST_inorder_terversal().
*/
void BST_inorder_terversal(Node *curr)
{
    if (curr == NULL)
        return;

    BST_inorder_terversal(curr->left);
    printf("%d ", curr->key);
    BST_inorder_terversal(curr->right);
}

/*
The parameter is a pointer to start themin_node search.

The return value is the pointer to the min_node.
*/
Node *min_node(Node *curr)
{
    if (curr->left == NULL)
        return curr;
    return min_node(curr->left);
}

/*
The parameters are the pointer to the starting node, and the key to be deleted.
*/
Node *BST_delete(Node *curr, int key)
{
    if (curr == NULL) {
        printf("The number %d doesn't exist.\n", key);
        return curr;
    }

    if (curr->key == key) {
        /*
        There are 3 cases for deletion.
        1. Node with no children. (leaf node)
        2. Node with one children.
        3. Node with two children.
        */

        if (curr->left == NULL && curr->right == NULL) { // case 1, leaf
            free(curr);
            return NULL;
        } else {
            if (!(curr->left != NULL && curr->right != NULL)) {
                // case 2, just move the child node to replace the deleted one.
                if (curr->left == NULL) {
                    Node *right = curr->right;
                    free(curr);
                    return right;
                } else {
                    Node *left = curr->left;
                    free(curr);
                    return left;
                }
            } else {
                // case 3, guaranteed to have 2 children
                Node *min_right_subtree_node = min_node(curr->right);
                Node *right = min_right_subtree_node->right;
                free(min_right_subtree_node);
                return right;
            }
        }
    } else if (curr->key < key) // go to right subtree
        curr->right = BST_delete(curr->right, key);
    else
        curr->left = BST_delete(curr->left, key);

    return curr;
}

/*
Prints the menu for BST homework.
Also, calls the appropriate functions to do the demanded jobs.
*/
void binary_search_tree()
{
    printf("==================\n");
    printf("Binary Search Tree\n");
    printf("==================\n\n");

    /*Initialization*/
    Node *BST_head = NULL;

    while (1) {
        printf("\nPlease make a choice: \n");
        printf("(I)nsert a number.\n");
        printf("(D)elete a number.\n");
        printf("(S)earch a number.\n");
        printf("(P)rint in infix & level order.\n");
        printf("(R)eturn\n\n");

        char command_prompt[1000];
        scanf("%s", command_prompt);

        char choice = command_prompt[0];
        if (choice == 'I' || choice == 'i') {
            // insert
            printf("Please enter a number: ");
            int key;
            scanf("%d", &key);

            BST_head = BST_insert(BST_head, key);
        } else if (choice == 'D' || choice == 'd') {
            // delete
            printf("Which number do you want to delete? ");
            int key;
            scanf("%d", &key);

            BST_head = BST_delete(BST_head, key);
        } else if (choice == 'S' || choice == 's') {
            // search
            printf("Which number do you want to search? ");
            int key;
            scanf("%d", &key);

            if (BST_search(BST_head, key) == NULL)
                printf("The number %d doesn't exist in the BST.\n\n", key);
            else
                printf("The number %d already exists.\n\n", key);
        } else if (choice == 'P' || choice == 'p') {
            // print
            printf("The tree in infix order: ");
            BST_inorder_terversal(BST_head);
            printf("\n");
        } else if (choice == 'R' || choice == 'r') {
            // return
            clear_screen();
            return;
        } else {
            printf("Invalid command\n");
        }
    }
}

int main()
{
    /*Initialization*/
    clear_screen();

    /*Program starts!*/
    while (1) {
        char choice = welcome_msg();

        if (choice == 'B' || choice == 'b') {
            binary_search_tree();
        } else if (choice == 'T' || choice == 't') {
            printf("===============\n");
            printf("Treasure Hunter\n");
            printf("===============\n");
        } else if (choice == 'E' || choice == 'e') {
            printf("=========\n");
            printf("Exit\n");
            printf("=========\n");
            break;
        } else {
            printf("=============\n");
            printf("Invalid input\n");
            printf("=============\n");
        }
    }

    return 0;
}
