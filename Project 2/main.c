#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define DEBUG 1

typedef struct node {

} Node;

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

void binary_search_tree()
{
    printf("==================\n");
    printf("Binary Search Tree\n");
    printf("==================\n\n");o
    
    while(1) {
	printf("(I)nsert a number.\n");
	printf("(D)elete a number.\n");
	printf("(S)earch a number.\n");
	printf("(P)rint in infix & level order.\n");
	printf("(R)eturn\n\n");

	char command_prompt[1000];
	scanf("%s", command_prompt);
	
	switch(command_prompt[0]) {
	    case 'I':
	    case 'i':
		//insert
		break;
	    case 'D':
	    case 'd':
		//delete
		break;
	    case 'S':
	    case 's':
		//search
		break;
	    case 'P':
	    case 'p':
		//print
		break;
	    case 'R':
	    case 'r':
		//return
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
