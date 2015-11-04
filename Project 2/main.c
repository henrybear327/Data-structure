#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define DEBUG 1
#define MAX_NODE 5000 // max node for queue to hold

typedef struct node {
    int key;
    struct node *left;
    struct node *right;

    bool exploded;
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

#if DEBUG == 1
    printf("Input received: %s\n", command_prompt);
#endif

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

    new_node->exploded = false;

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

#if DEBUG == 1
/*
More info BST_inorder_terversal() for debugging
*/
void BST_inorder_terversal_verbose(Node *curr)
{
    if (curr == NULL)
        return;

    printf("Traversal %p curr = %d, left %p, right %p\n", curr, curr->key,
           curr->left, curr->right);

    BST_inorder_terversal_verbose(curr->left);

    printf("Traversal print %p curr = %d, left %p, right %p\n", curr, curr->key,
           curr->left, curr->right);

    BST_inorder_terversal_verbose(curr->right);
}
#endif

/*
The parameter is a pointer to start the min_node search.

The return value is the pointer to the min_node.
*/
Node *min_node(Node *curr)
{
    if (curr->left == NULL)
        return curr;
    return min_node(curr->left);
}

/*
The parameter is the starting node pointer to be searched.

The return value is the pointer to the previous node of the min_node.
If the node passed in can't be used to find prev_min_node, NULL is returned.
*/
Node *prev_min_node(Node *curr, int key)
{
    if (curr->key ==
        key) // the node passed in can't be used to find prev_min_node
        return NULL;

    if (curr->left->key == key) // fonud
        return curr;

    return prev_min_node(curr->left, key);
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
#if DEBUG == 1
            printf("Deletion case 1\n");
#endif
            free(curr);
            return NULL;
        } else {
            if (!(curr->left != NULL && curr->right != NULL)) {
#if DEBUG == 1
                printf("Deletion case 2\n");
#endif
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
#if DEBUG == 1
                printf("Deletion case 3\n");
#endif
                // case 3, guaranteed to have 2 children
                Node *min_right_subtree_node = min_node(curr->right);
#if DEBUG == 1
                printf("curr %d, min_key %d\n", curr->key, min_right_subtree_node->key);
#endif

                // deal with the min_node, find prev
                Node *prev_min_node_ptr =
                    prev_min_node(curr->right, min_right_subtree_node->key);
#if DEBUG == 1
                printf("prev %d\n",
                       prev_min_node_ptr == NULL ? -1 : prev_min_node_ptr->key);
#endif

                // update curr
                curr->key = min_right_subtree_node->key;

                if (prev_min_node_ptr == NULL) {
                    assert(curr->right == min_right_subtree_node);
                    curr->right = min_right_subtree_node->right;
                    free(min_right_subtree_node);
                } else {
                    assert(prev_min_node_ptr->left == min_right_subtree_node);
                    prev_min_node_ptr->left = min_right_subtree_node->right;
                    free(min_right_subtree_node);
                }

                return curr;
            }
        }
    } else if (curr->key < key) // go to right subtree
        curr->right = BST_delete(curr->right, key);
    else
        curr->left = BST_delete(curr->left, key);

    return curr;
}

/*
The parameters are the starting and ending idx of the queue

If empty, return true. Otherwise, return false.
*/
bool is_queue_empty(int q_start, int q_end)
{
    return q_start == q_end;
}

/*
The parameters are the pointer to the queue, the starting and ending idx of the
queue.

Return value is the front node.

Warning! No empty queue check is performed.
*/
Node *queue_front(Node *queue[], int *q_start, int *q_end)
{
    assert(*q_start <= *q_end);
    return queue[(*q_start)];
}

/*
The parameters are the pointers of starting and ending idx of the queue
*/
bool queue_pop(int *q_start, int *q_end)
{
    if (is_queue_empty(*q_start, *q_end) == true)
        return false;

    (*q_start)++;
    return true;
}

/*
The parameters are the pointer to the queue, the starting and ending idx of the
queue,
and the Node to enqueue.

Return value is the front node.
*/
bool queue_push(Node *queue[], int *q_start, int *q_end, Node *enqueue)
{
    assert(*q_start <= *q_end);
    assert(*q_end < MAX_NODE);

    queue[(*q_end)++] = enqueue;
    return true;
}

void BST_level_order_terversal(Node *head)
{
    if (head == NULL)
        return;

    Node *queue[MAX_NODE];

    int q_start = 0, q_end = 0;

    queue_push(queue, &q_start, &q_end, head);
    while (is_queue_empty(q_start, q_end) == false) {
        Node *top_element = queue_front(queue, &q_start, &q_end);
        printf("%d ", top_element->key);

        if (top_element->left != NULL)
            queue_push(queue, &q_start, &q_end, top_element->left);
        if (top_element->right != NULL)
            queue_push(queue, &q_start, &q_end, top_element->right);

        queue_pop(&q_start, &q_end);
    }
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
#if DEBUG == 1
        printf("(V)erbosely print in infix order\n");
#endif
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
                printf("The number %d exists in the BST.\n\n", key);
        } else if (choice == 'P' || choice == 'p') {
            // print
            printf("The tree in infix order: ");
            BST_inorder_terversal(BST_head);
            printf("\n");

            printf("The tree in level order: ");
            BST_level_order_terversal(BST_head);
            printf("\n");
        }
#if DEBUG == 1
        else if (choice == 'V' || choice == 'v') {
            printf("The tree in infix order (verbosely):\n");
            BST_inorder_terversal_verbose(BST_head);
            printf("\n");
        }
#endif
        else if (choice == 'R' || choice == 'r') {
            // return
            clear_screen();

            /*Should perform free() to all nodes using inorder traversal*/

            return;
        } else {
            printf("Invalid command\n");
        }
    }
}

bool has_eight(int val)
{
    while (val) {
        if (val % 10 == 8)
            return true;
        val /= 10;
    }

    return false;
}

Node *modified_BST_search(Node *curr, int key, bool print_info)
{
    if (curr == NULL)
        return NULL;

    if (print_info)
        printf("%d ", curr->key);

    if (has_eight(curr->key) && curr->exploded == false) {
        curr->exploded = true;
        if (curr->left == NULL) {
            if (curr->right != NULL)
                curr = BST_delete(curr, curr->right->key);
        } else {
            curr = BST_delete(curr, curr->left->key);
        }
    }

    if (curr->key == key)
        return curr;
    else {
        if (curr->key < key) // right subtree
            return modified_BST_search(curr->right, key, false);
        else // left subtree
            return modified_BST_search(curr->left, key, false);
    }
}

void treasure_hunter()
{
    printf("===============\n");
    printf("Treasure Hunter\n");
    printf("===============\n");

    printf("Please input the name of the map file without spaces: ");
    char filename[1000];
    scanf("%s", filename);

    // can't use freopen because stdin will be changed to file!
    FILE *fptr = fopen(filename, "r");
    if (fptr == NULL) {
        printf("The filename you entered wasn't correct! Returning to menu...\n\n");
        return;
    } else {
        printf("The file was loaded successfully!\n\n");
    }

    /*Initialization*/
    Node *BST_head = NULL;

    // create BST
    int inp;
    // bool number_exists[MAX_NUM_RANGE] = {false};
    while (fscanf(fptr, "%d", &inp) != EOF) {
        BST_head = BST_insert(BST_head, inp);
        // number_exists[inp] = true;
    }
    fclose(fptr);

#if DEBUG == 1
    printf("The tree in infix order before using modified_BST_search: ");
    BST_inorder_terversal(BST_head);
    printf("\n");

    printf("The tree in level order before using modified_BST_search: ");
    BST_level_order_terversal(BST_head);
    printf("\n");
#endif

    if (BST_head == NULL) {
        printf("Empty file!! Returning to menu now...\n\n");
        return;
    }

    // Prompt the user for the key and Treasure
    printf("Please input the key location: ");
    int key_loc;
    scanf("%d", &key_loc);

    printf("Please input the treasure location: ");
    int treasure_loc;
    scanf("%d", &treasure_loc);

    bool key_exist = true, treasure_exist = true;
    /*
    if (number_exists[key_loc] == false ||
        modified_BST_search(BST_head, key_loc, false) == NULL) {
    */
    if (modified_BST_search(BST_head, key_loc, false) == NULL) {
        /*
        if (number_exists[key_loc] == true) {
            printf("The key is burned while searching!!\n");
        }
        */
        key_exist = false;
        printf("Key is not found.\n");
    }

    /*
    if (number_exists[treasure_loc] == false ||
        modified_BST_search(BST_head, treasure_loc, false) == NULL) {
    */
    if (modified_BST_search(BST_head, treasure_loc, false) == NULL) {
        /*
        if (number_exists[treasure_loc] == true) {
            printf("The treasure is burned while searching!!\n");
        }
        */
        treasure_exist = false;
        printf("Treasure is not found.\n");
    }

#if DEBUG == 1
    printf("The tree in infix order after using modified_BST_search: ");
    BST_inorder_terversal(BST_head);
    printf("\n");

    printf("The tree in level order after using modified_BST_search: ");
    BST_level_order_terversal(BST_head);
    printf("\n");
#endif

    return;
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
            treasure_hunter();
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
