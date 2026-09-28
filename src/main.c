#include <stdio.h>
#include <string.h>

#include "table.h"
#include "parser.h"
#include "database.h"

#define MAX_INPUT_SIZE 256

int main(void)
{
    char input[MAX_INPUT_SIZE];
    char table_name[MAX_TABLE_NAME_LENGTH];

    Database database;

    init_database(&database);

    printf("=================================\n");
    printf("      CDB Database Engine\n");
    printf("          Version 0.1\n");
    printf("=================================\n");

    while (1)
    {
        printf("CDB> ");

        if (fgets(input, sizeof(input), stdin) == NULL)
        {
            break;
        }

        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }
        else if (strcmp(input, "help") == 0)
        {
            printf("\nAvailable commands:\n");
            printf("  help\n");
            printf("  tables\n");
            printf("  CREATE TABLE <name>\n");
            printf("  exit\n\n");
        }
        else if (strcmp(input, "tables") == 0)
        {
            print_database(&database);
        }
        else if (parse_create_table(input, table_name))
        {
            if (add_table(&database, table_name))
            {
                printf("Table created successfully.\n");
            }
            else
            {
                printf("Failed to create table.\n");
            }
        }
        else if (strlen(input) == 0)
        {
            continue;
        }
        else
        {
            printf("Unknown command: %s\n", input);
        }
    }

    return 0;
}
