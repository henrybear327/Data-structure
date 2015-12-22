#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#define DEBUG 1

#define DATA_ROW 500

typedef struct {
    int id;
    char FirstName[20], LastName[20], Gender[5];
    int Age;
    char PhoneNum[20];
} Data;

int data_idx;
Data data[DATA_ROW];

void read_data(char *file_path)
{
    // init.
    memset(data, 0, sizeof(data));

    // clean up \n\r for file_path
    int len = strlen(file_path);
    for (int i = 0; i < len; i++)
        if (file_path[i] == '\n' || file_path[i] == '\r')
            file_path[i] = '\0';

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
        for (int i = 0; input[i] != '\0'; i++) {
            if (input[i] == '\"' || input[i] == ',')
                input[i] = ' ';
        }
        sscanf(input, "%d %s %s %s %d %s", &data[data_idx].id, data[data_idx].FirstName,
               data[data_idx].LastName, data[data_idx].Gender, &data[data_idx].Age, data[data_idx].PhoneNum);
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

int main()
{
    char input[10000];
    while (fgets(input, 10000, stdin) != NULL) {
        read_data("Contacts.csv");
    }

    return 0;
}
