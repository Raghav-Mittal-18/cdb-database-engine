#include "executor.h"
#include <stdio.h>
#include <string.h>

static int find_column_index(
    const Table *table,
    const char *column_name
)
{
    for (int i = 0; i < table->column_count; i++)
    {
        if (strcmp(
                table->columns[i].name,
                column_name) == 0)
        {
            return i;
        }
    }

    return -1;
}

void execute_select(
    Database *database,
    const char *table_name,
    const char *condition_column,
    const char *condition_value
)
{
    Table *table = get_table(database, table_name);

    if (table == NULL)
    {
        printf("Table '%s' does not exist.\n", table_name);
        return;
    }

    /*
     * No WHERE condition.
     *
     * Example:
     * SELECT * FROM students
     */
    if (condition_column[0] == '\0')
    {
        print_records(table);
        return;
    }

    /*
     * WHERE condition exists.
     *
     * Example:
     * SELECT * FROM students WHERE age = 21
     */
    int column_index =
        find_column_index(table, condition_column);

    if (column_index == -1)
    {
        printf("Column '%s' does not exist.\n",
               condition_column);
        return;
    }


    /*
     * Actual record filtering will be added here.
     */
    int found = 0;

for (int i = 0; i < table->record_count; i++)
{
    int matches = 0;

    if (table->columns[column_index].type == TYPE_INT)
    {
        int condition_number;

        if (sscanf(condition_value, "%d",
                   &condition_number) != 1)
        {
            printf("Invalid integer value: %s\n",
                   condition_value);
            return;
        }

        if (table->records[i]
                .values[column_index]
                .int_value == condition_number)
        {
            matches = 1;
        }
    }
    else if (table->columns[column_index].type == TYPE_TEXT)
    {
        if (strcmp(
                table->records[i]
                    .values[column_index]
                    .text_value,
                condition_value) == 0)
        {
            matches = 1;
        }
    }

    if (matches)
    {
        printf("Record %d: ", i + 1);

        for (int j = 0;
             j < table->column_count;
             j++)
        {
            if (table->columns[j].type == TYPE_INT)
            {
                printf("%d",
                       table->records[i]
                           .values[j]
                           .int_value);
            }
            else if (table->columns[j].type == TYPE_TEXT)
            {
                printf("%s",
                       table->records[i]
                           .values[j]
                           .text_value);
            }

            if (j < table->column_count - 1)
            {
                printf(" | ");
            }
        }

        printf("\n");

        found = 1;
    }
}

if (!found)
{
    printf("No matching records found.\n");
}
}
