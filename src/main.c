#include <stdio.h>
#include <string.h>

#include "table.h"
#include "parser.h"
#include "database.h"
#include "executor.h"

#define MAX_INPUT_SIZE 256

int main(void)
{
    char input[MAX_INPUT_SIZE];

    char table_name[MAX_TABLE_NAME_LENGTH];
    char column_definitions[256];
    char values[256];

    char condition_column[MAX_COLUMN_NAME_LENGTH];
    char condition_value[MAX_TEXT_LENGTH];

    char set_column[MAX_COLUMN_NAME_LENGTH];
    char set_value[MAX_TEXT_LENGTH];

    static Database database;

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

        /*
         * EXIT
         */
        if (strcmp(input, "exit") == 0)
        {
            printf("Goodbye!\n");
            break;
        }

        /*
         * HELP
         */
        else if (strcmp(input, "help") == 0)
        {
            printf("\nAvailable commands:\n");
            printf("  help\n");
            printf("  tables\n");
            printf("  CREATE TABLE <name> (...)\n");
            printf("  INSERT INTO <table> VALUES (...)\n");
            printf("  SELECT * FROM <table>\n");
            printf("  SELECT * FROM <table> WHERE <column> = <value>\n");
            printf("  UPDATE <table> SET <column> = <value> WHERE <column> = <value>\n");
            printf("  exit\n\n");
        }

        /*
         * LIST TABLES
         */
        else if (strcmp(input, "tables") == 0)
        {
            printf("\n");

            print_database(&database);

            for (int i = 0;
                 i < database.table_count;
                 i++)
            {
                print_records(&database.tables[i]);
            }
        }

        /*
         * CREATE TABLE
         */
        else if (parse_create_table(input, table_name))
        {
            if (!extract_column_definitions(
                    input,
                    column_definitions))
            {
                printf("Invalid column definitions.\n");
                continue;
            }

            if (!add_table(&database, table_name))
            {
                printf("Failed to create table.\n");
                continue;
            }

            Table *table =
                get_table(&database, table_name);

            if (table == NULL)
            {
                printf("Failed to access created table.\n");
                continue;
            }

            if (!parse_column_definitions(
                    column_definitions,
                    table))
            {
                printf("Invalid column definition.\n");
                continue;
            }

            printf("Table created successfully.\n");
        }

        /*
         * INSERT
         */
        else if (parse_insert(
                     input,
                     table_name,
                     values))
        {
            Table *table =
                get_table(&database, table_name);

            if (table == NULL)
            {
                printf(
                    "Table '%s' does not exist.\n",
                    table_name
                );

                continue;
            }

            Record record;

            init_record(&record);

            if (!parse_values(
                    values,
                    table,
                    &record))
            {
                printf("Invalid values.\n");
                continue;
            }

            if (!add_record(
                    table,
                    &record))
            {
                printf("Failed to insert record.\n");
                continue;
            }

            printf("Record inserted successfully.\n");
        }

        /*
         * SELECT
         */
        else if (parse_select(
                     input,
                     table_name,
                     condition_column,
                     condition_value))
        {
            execute_select(
                &database,
                table_name,
                condition_column,
                condition_value
            );
        }

        /*
         * UPDATE
         */
        else if (parse_update(
                     input,
                     table_name,
                     set_column,
                     set_value,
                     condition_column,
                     condition_value))
        {
            execute_update(
                &database,
                table_name,
                set_column,
                set_value,
                condition_column,
                condition_value
            );
        }

        /*
         * EMPTY INPUT
         */
        else if (strlen(input) == 0)
        {
            continue;
        }

        /*
         * UNKNOWN COMMAND
         */
        else
        {
            printf(
                "Unknown command: %s\n",
                input
            );
        }
    }

    return 0;
}
