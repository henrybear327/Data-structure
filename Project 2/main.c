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

void clear_screen()
{
    printf("\033[2J");
}

int welcome_msg()
{
    printf("(B)inary Search Tree.\n");
    printf("(T)reasure Hunter\n");
    printf("(E)xit\n");

    char command_prompt[1000];
    scanf("%s", command_prompt);

    return command_prompt[0];
}

Node *create_node()
{
    Node *new = malloc(sizeof(Node));
    assert(new != NULL);

    new->data = 0;
    new->left = NULL;
    new->right = NULL;

    return new;
}

Node *BST_search(Node *curr, int key)
{
    if (curr != NULL)
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

        switch (command_prompt[0]) {
        case 'I':
        case 'i':
            // insert
            BST_insert();
            break;
        case 'D':
        case 'd':
            // delete
            break;
        case 'S':
        case 's':
            // search
            break;
        case 'P':
        case 'p':
            // print
            break;
        case 'R':
        case 'r':
            // return
            break;
        default:
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
