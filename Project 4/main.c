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

int total_command;

const char *core_command[3] = {"select", "from",
                               "order by"
                              }; // case-insensitive
int core_command_location[3];               // select from order by

const char *column_name[6] = {"Id",     "FirstName", "LastName",
                              "Gender", "Age",       "PhoneNum"
                             };
bool show_column[6];

// define state constant
#define ERROR 0
#define PASS_CHECKS 1
#define QUIT 2

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

int get_column(char *name)
{
    for (int i = 0; i < 6; i++) {
        if (strcmp(column_name[i], name) == 0)
            return i;
    }
    return -1;
}

int get_order_by_param(char *param)
{
    if (strcmp(param, "ASC") == 0)
        return 6;
    else if (strcmp(param, "DESC") == 0)
        return 7;
    else
        return -1;
}

int get_order_by_sorting(char *param)
{
    if (strcmp(param, "-1") == 0)
        return 8;
    else if (strcmp(param, "-2") == 0)
        return 9;
    else
        return -1;
}

/*
This function reads the data from the .csv file
and stores the data in the data array of structure.
*/
bool read_data(char *file_path)
{
    // init.
    memset(data, 0, sizeof(data));

    // clean up \n\r for file_path
    sanitize_string(file_path);

    FILE *pFile = fopen(file_path, "r");
    if (pFile == NULL) {
        printf("This file does not exist!\n");
        return false;
    }

    data_idx = 0;
    char input[10000];
    while (fgets(input, 10000, pFile) != NULL) {
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
        printf("Record %d: %s %s %s %d %s\n", data[i].id, data[i].FirstName,
               data[i].LastName, data[i].Gender, data[i].Age, data[i].PhoneNum);
    }
    printf("\n");
#endif

    fclose(pFile);
    return true;
}

void string_to_lower(char *input)
{
    int len = strlen(input);
    for (int i = 0; i < len; i++) {
        if ('A' <= input[i] && input[i] <= 'Z')
            input[i] = input[i] - 'A' + 'a';
    }
}

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

/*
Checks if select, from, and order by is present.
If yes, record their positions.

Checks for duplicated core commands. (confirmed by TA, no need to check)
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
                        core_command_location[0] = i;
                    else
                        return false;
                } else if (j == 1) {
                    has_from = true;
                    if (core_command_location[1] == -1)
                        core_command_location[1] = i;
                    else
                        return false;
                } else {
                    if (core_command_location[2] == -1)
                        core_command_location[2] = i;
                    else
                        return false;
                }
            }
        }
    }

    for (int i = 1; i < (core_command_location[2] == -1 ? 2 : 3); i++) {
        if (core_command_location[i] < core_command_location[i - 1])
            return false;
    }

    if (has_select && has_from) {
#if DEBUG == 1
        printf("SELECT and FROM is present\n");
#endif
        return true;
    } else {
#if DEBUG == 1
        printf("SELECT and FROM is missing\n");
#endif
        return false;
    }
}

/*
Confirmed by TA, no need to check for upper/lower letter errors
*/
bool check_column_name(char input_token[50][20])
{
    memset(show_column, false, sizeof(show_column));

    // get the select starting and ending position
    int start = core_command_location[0];
    int end = core_command_location[1];

    for (int i = start + 1; i < end; i++) {
        if (strcmp("*", input_token[i]) == 0) {
#if DEBUG == 1
            printf("Show all columns\n");
#endif
            for (int j = 0; j < 6; j++)
                show_column[j] = true;

            return true;
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
    printf("Columns are found and show_column is set\n");
#endif
    return true;
}

int sorting_parameter[6];
bool get_order_by_command(char input_token[50][20])
{
    memset(sorting_parameter, -1, sizeof(sorting_parameter));
    sorting_parameter[1] = sorting_parameter[4] = 1; // default ASC

    bool is_first = true;
    for (int i = core_command_location[2] + 1; i < total_command; i++) {
        int result;
        if ((result = get_column(input_token[i])) == -1) {
            if ((result = get_order_by_param(input_token[i])) == -1) {
                if ((result = get_order_by_sorting(input_token[i])) == -1) {
                    return false;
                }
            }
        }

        if (result < 6) {
            if (sorting_parameter[0] != -1) {
                is_first = false;
                sorting_parameter[3] = result;
            } else
                sorting_parameter[0] = result;
        } else if (result == 6 || result == 7) {
            // 1 for ASC, 2 for DESC
            if (is_first == false)
                sorting_parameter[4] = result - 5;
            else
                sorting_parameter[1] = result - 5;
        } else {
            // 1 for sotring 1, 2 for sorting 2
            if (is_first == false)
                sorting_parameter[5] = result - 7;
            else
                sorting_parameter[2] = result - 7;
        }
    }

    assert(sorting_parameter[0] != -1);
#if DEBUG == 1
    printf("Order by paramenetr: ");
    for (int i = 0; i < 6; i++) {
        printf("%d%c", sorting_parameter[i], i == 5 ? '\n' : ' ');
    }
    printf("\n");
#endif

    return true;
}

/*
This function parses the input and identifies errors.

The return value is an integer, where 0 is an input with errors,
1 is an input to be executed, and 2 being the quit command.
*/

int parse_input(char *input, char input_token[50][20],
                char input_token_lower[50][20])
{
    // clear \n \r
    sanitize_string(input);

    if (strcmp(input, "quit") == 0)
        return QUIT;
    else {
        // split the input
        split_input(input, input_token, input_token_lower);

#if DEBUG == 1
        printf("================================================\n");
        printf("Parsed input:\n");
        for (int i = 0; i < total_command; i++) {
            printf("%s ", input_token[i]);
        }
        printf("\n");

        printf("Parsed input to lower:\n");
        for (int i = 0; i < total_command; i++) {
            printf("%s ", input_token_lower[i]);
        }
        printf("\n\n");
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

        // parse order by if order by command is present
        if (core_command_location[2] != -1) {
            if (get_order_by_command(input_token) == false) {
                printf("You have an error in your SQL syntax.\n");
                return ERROR;
            }
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
        char input_token[50][20], input_token_lower[50][20];
        int result = parse_input(input, input_token, input_token_lower);

        if (result == ERROR)
            continue;
        else if (result == QUIT)
            return 0;
        else {
            // read data from .cvs using info from core_command_location[1] + 1
            if (read_data(input_token[core_command_location[1] + 1]) == false) {
                continue;
            }

// passed all input checks
// know what column to print now
#if DEBUG == 1
            printf("All checks passed!\n\n");
#endif
        }
    }

    return 0;
}
