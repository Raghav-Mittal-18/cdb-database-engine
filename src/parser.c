#include "parser.h"
#include <string.h>
#include <stdio.h>

int parse_create_table(
    const char *input,
    char *table_name
)
{
    const char *prefix = "CREATE TABLE ";
    const char *open_paren;
    size_t prefix_length;
    size_t table_name_length;

    prefix_length = strlen(prefix);

    if (strncmp(input, prefix, prefix_length) != 0)
    {
        return 0;
    }

    open_paren = strchr(input + prefix_length, '(');

    if (open_paren == NULL)
    {
        return 0;
    }

    table_name_length = (size_t)(open_paren - (input + prefix_length));

    if (table_name_length == 0 ||
        table_name_length >= MAX_TABLE_NAME_LENGTH)
    {
        return 0;
    }

    strncpy(
        table_name,
        input + prefix_length,
        table_name_length
    );

    table_name[table_name_length] = '\0';

    return 1;
}

int extract_column_definitions(
    const char *input,
    char *column_definitions
)
{
    const char *open_paren;
    const char *close_paren;
    size_t definition_length;

    open_paren = strchr(input, '(');
    close_paren = strrchr(input, ')');

    if (open_paren == NULL || close_paren == NULL)
    {
        return 0;
    }

    if (close_paren <= open_paren)
    {
        return 0;
    }

    definition_length =
        (size_t)(close_paren - open_paren - 1);

    if (definition_length == 0)
    {
        return 0;
    }

    strncpy(
        column_definitions,
        open_paren + 1,
        definition_length
    );

    column_definitions[definition_length] = '\0';

    return 1;
}

int parse_column_definitions(
    const char *column_definitions,
    Table *table
)
{
    char definitions[256];
    char *definition;

    strncpy(definitions, column_definitions, sizeof(definitions) - 1);
    definitions[sizeof(definitions) - 1] = '\0';

    definition = strtok(definitions, ",");

    while (definition != NULL)
    {
        char column_name[MAX_COLUMN_NAME_LENGTH];
        char type_name[16];

        if (sscanf(definition, "%63s %15s",
                   column_name, type_name) != 2)
        {
            return 0;
        }

        if (strcmp(type_name, "INT") == 0)
        {
            if (!add_column(table, column_name, TYPE_INT))
            {
                return 0;
            }
        }
        else if (strcmp(type_name, "TEXT") == 0)
        {
            if (!add_column(table, column_name, TYPE_TEXT))
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }

        definition = strtok(NULL, ",");
    }

    return 1;
}
