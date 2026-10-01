#include "table.h"
#include <string.h>
#include <stdio.h>

Table create_table(const char *name)
{
    Table table;

    strncpy(table.name, name, MAX_TABLE_NAME_LENGTH - 1);
    table.name[MAX_TABLE_NAME_LENGTH - 1] = '\0';

    table.column_count = 0;
    table.record_count = 0;

    return table;
}

int add_column(Table *table, const char *column_name, DataType type)
{
    if (table->column_count >= MAX_COLUMNS)
    {
        return 0;
    }

    Column *column = &table->columns[table->column_count];

    strncpy(column->name,
            column_name,
            MAX_COLUMN_NAME_LENGTH - 1);

    column->name[MAX_COLUMN_NAME_LENGTH - 1] = '\0';

    column->type = type;

    table->column_count++;

    return 1;
}

const char *data_type_to_string(DataType type)
{
    switch (type)
    {
        case TYPE_INT:
            return "INT";

        case TYPE_TEXT:
            return "TEXT";

        default:
            return "UNKNOWN";
    }
}

void print_table(const Table *table)
{
    printf("Table name: %s\n", table->name);
    printf("Column count: %d\n", table->column_count);
    printf("Record count: %d\n", table->record_count);

    if (table->column_count > 0)
    {
        printf("Columns:\n");

        for (int i = 0; i < table->column_count; i++)
        {
            printf("  %d. %s (%s)\n",
                   i + 1,
                   table->columns[i].name,
                   data_type_to_string(table->columns[i].type));
        }
    }
}

int add_record(Table *table, const Record *record)
{
    if (table->record_count >= MAX_RECORDS)
    {
        return 0;
    }

    table->records[table->record_count] = *record;
    table->record_count++;

    return 1;
}

void print_records(const Table *table)
{
    if (table->record_count == 0)
    {
        printf("No records found.\n");
        return;
    }

    printf("\nRecords:\n");

    for (int i = 0; i < table->record_count; i++)
    {
        printf("Record %d: ", i + 1);

        for (int j = 0; j < table->column_count; j++)
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
    }
}
