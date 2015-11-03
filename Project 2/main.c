#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define DEBUG 1

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} Node;

Node *BST_start_ptr;

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
    printf("(B)inary Search Tree.\n");
    printf("(T)reasure Hunter\n");
    printf("(E)xit\n");

    char command_prompt[1000];
    scanf("%s", command_prompt);

    return command_prompt[0];
}

/*
If a new node is successfully created, the return value will be a pointer to the
newly created node.
Also, the node will be initialized with data = 0, and left and right pointer to
NULL.
*/
Node *create_node()
{
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);

    // init.
    new->data = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

/*
If the key is found, the return value will be the pointer to that node.
Otherwise, the return value is NULL.
*/
Node *BST_search(Node *curr, int key)
{
    if (curr == NULL)
        return NULL;
    else if (curr->data == key)
        return curr;
    else {
        if (curr->data < key)
            return BST_search(curr->right, key);
        else
            return BST_search(curr->left, key);
    }
}

/*
Get the value to be inserted.

The function first checks for duplicated key.
If this happenes, the key is not inserted.
Otherwise, the key will be inserted according to the BST rule.
*/
void BST_insert()
{
    printf("Please enter a number: ");
    int key;
    scanf("%d", &key);

    if (BST_search(BST_start_ptr, key) != NULL) {
        printf("The number %d already exists.\n", key);
        return;
    }

    if (BST_start_ptr == NULL) {
        BST_start_ptr = create_node();
        BST_start_ptr->data = key;
    } else {
        Node *curr = BST_start_ptr;
        Node *to_insert = create_node();
        to_insert->data = key;
        while (1) {
            if (key > curr->data) {
                if (curr->right == NULL) {
                    curr->right = to_insert;
                    break;
                } else {
                    curr = curr->right;
                }
            } else {
                if (curr->left == NULL) {
                    curr->left = to_insert;
                    break;
                } else {
                    curr = curr->left;
                }
            }
        }
    }
}

/*
Perform an inorder traversal on the given BST tree.
*/
void BST_inorder_terversal(Node *curr)
{
    if (curr == NULL)
        return;

    BST_inorder_terversal(curr->left);
    printf("%d \n", curr->data);
    BST_inorder_terversal(curr->right);
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

    // Init.
    BST_start_ptr = NULL;

    while (1) {
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
            BST_insert();
        } else if (choice == 'D' || choice == 'd') {
            // delete
        } else if (choice == 'S' || choice == 's') {
            // search
            printf("Which number do you want to search? ");
            int key;
            scanf("%d", &key);
            if (BST_search(BST_start_ptr, key) == NULL)
                printf("The number %d doesn't exist in the BST.\n\n", key);
            else
                printf("The number %d is in the tree.\n\n", key);
        } else if (choice == 'P' || choice == 'p') {
            // print
            BST_inorder_terversal(BST_start_ptr);
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
    clear_screen();

    while (1) {
        char choice = welcome_msg();
#if DEBUG
        printf("input = %c\n", choice);
#endif
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
