#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <ctype.h>

// debug mode switch
#define DEBUG 1

// total data that can be added to the database
#define DATA_ROW 500

typedef struct {
    int id;
    char FirstName[20], LastName[20], Gender[5];
    int Age;
    char PhoneNum[20];
} Data;

int data_idx;
Data data[DATA_ROW];

/*
Remove \n\r from the string
*/
void sanitize_string(char *input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++)
        if (input[i] == '\n' || input[i] == '\r')
            input[i] = '\0';
}

/*
This function reads the data from the .csv file
and stores the data in the data array of structure.
*/
void read_data(char *file_path)
{
    // init.
    memset(data, 0, sizeof(data));

    // clean up \n\r for file_path
    sanitize_string(file_path);

#if DEBUG == 1
    printf("file_path: %s\n", file_path);
#endif

    FILE *pFile = fopen(file_path, "r");
    assert(pFile != NULL);

    data_idx = 0;
    char input[10000];
    while (fgets(input, 10000, pFile) != NULL) {
#if DEBUG == 1
        printf("%s", input);
#endif
        // change all " and , to space in order for scanf to work
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\"' || input[i] == ',')
                input[i] = ' ';
        }
        sscanf(input, "%d %s %s %s %d %s", &data[data_idx].id,
               data[data_idx].FirstName, data[data_idx].LastName,
               data[data_idx].Gender, &data[data_idx].Age, data[data_idx].PhoneNum);
        data_idx++;
    }

#if DEBUG == 1
    printf("\n");
    for (int i = 0; i < data_idx; i++) {
        printf("Record %d: %d %s %s %s %d %s\n", i, data[i].id, data[i].FirstName,
               data[i].LastName, data[i].Gender, data[i].Age, data[i].PhoneNum);
    }
    printf("\n");
#endif

    fclose(pFile);
}

void string_to_lower(char *input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if ('A' <= input[i] && input[i] <= 'Z')
            input[i] = input[i] - 'A' + 'a';
    }
}

int total_command;
void split_input(char *input, char input_token[50][20],
                 char input_token_lower[50][20])
{
    total_command = 0;
    char *command = strtok(input, " ,\n\r");
    while (command != NULL) {
        strcpy(input_token[total_command], command);
        strcpy(input_token_lower[total_command], command);
        string_to_lower(input_token_lower[total_command]);
        total_command++;

        command = strtok(NULL, " ,\n\r");
    }
}

const char *core_command[3] = {"select", "from",
                               "order by"
                              }; // case-insensitive
int core_command_location[3];               // select from order by

/*
Checks is select, from, and order by is present.
If yes, record their position, too.

Checks for duplicated core command, too.
*/
bool check_core_command_present(char input_token_lower[50][20])
{
    memset(core_command_location, -1, sizeof(core_command_location));

    bool has_select = false, has_from = false;
    for (int i = 0; i < total_command; i++) {
        for (int j = 0; j < 3; j++) {
            if (strcmp(input_token_lower[i], core_command[j]) == 0) {
                if (j == 0) {
                    has_select = true;
                    if (core_command_location[0] == -1)
                        core_command_location[0] = j;
                    else
                        return false;
                } else if (j == 1) {
                    has_from = true;
                    if (core_command_location[1] == -1)
                        core_command_location[1] = j;
                    else
                        return false;
                } else {
                    if (core_command_location[2] == -1)
                        core_command_location[2] = j;
                    else
                        return false;
                }
            }
        }
    }

    if (has_select && has_from) {
#if DEBUG == 1
        printf("SELECT and FROM is present\n");
#endif
        return true;
    } else {
        return false;
    }
}

const char *column_name[6] = {"Id",     "FirstName", "LastName",
                              "Gender", "Age",       "PhoneNum"
                             };
bool show_column[6];
bool check_column_name(char input_token[50][20])
{
    memset(show_column, false, sizeof(show_column));

    // get the select starting and ending position
    int start = core_command_location[0];
    int end = core_command_location[1];

    for (int i = start + 1; i < end; i++) {
        if (strcmp("*", input_token[i])) {
#if DEBUG == 1
            printf("Show all columns\n");
#endif
            for (int j = 0; j < 6; j++)
                show_column[j] = true;
        } else {
            bool found = false;
            for (int j = 0; j < 6; j++) {
                if (strcmp(column_name[j], input_token[i]) == 0) {
                    found = true;
                    show_column[j] = true;
                    break;
                }
            }

            if (found == false) {
#if DEBUG == 1
                printf("%s not found\n", input_token[i]);
#endif
                return false;
            }
        }
    }

#if DEBUG == 1
    printf("Columns are found and set\n");
#endif
    return true;
}

/*
This function parses the input and identify errors.

The return value is a integer, where 0 is an input with errors,
1 is an input to be executed, and 2 being the quit command.
*/

// define state constant
#define ERROR 0
#define PASS_CHECKS 1
#define QUIT 2

int parse_input(char *input)
{
    // clear \n \r
    sanitize_string(input);

    if (strcmp(input, "quit") == 0)
        return QUIT;
    else {
        // split the input
        char input_token[50][20], input_token_lower[50][20];
        split_input(input, input_token, input_token_lower);

#if DEBUG == 1
        printf("Parsed input: ");
        for (int i = 0; i < total_command; i++) {
            printf("%s ", input_token[i]);
        }
        printf("\n");

        printf("Parsed input to lower: ");
        for (int i = 0; i < total_command; i++) {
            printf("%s ", input_token_lower[i]);
        }
        printf("\n");
#endif

        // check if select and from exist
        if (check_core_command_present(input_token_lower) == false) {
            printf("You have an error in your SQL syntax.\n");
            return ERROR;
        }

        // check for column names correctness
        if (check_column_name(input_token) == false) {
            printf("You have an error in your SQL syntax.\n");
            return ERROR;
        }
    }

    return PASS_CHECKS;
}

int main()
{
    char input[10000];
    while (fgets(input, 10000, stdin) != NULL) {
        // read_data("Contacts.csv"); // debug file

        // check input
        int result = parse_input(input);
        if (result == ERROR)
            continue;
        else if (result == QUIT)
            return 0;
        else {
            // passed all input checks
            // know what column to print now
        }
    }

    return 0;
}
