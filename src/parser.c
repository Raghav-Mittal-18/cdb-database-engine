#include "parser.h"
#include <string.h>
#include <stdio.h>
#include <ctype.h>

static void trim_whitespace(char *text)
{
    char *start = text;
    char *end;

    while (isspace((unsigned char)*start))
    {
        start++;
    }

    if (*start == '\0')
    {
        text[0] = '\0';
        return;
    }

    end = start + strlen(start) - 1;

    while (end > start &&
           isspace((unsigned char)*end))
    {
        end--;
    }

    *(end + 1) = '\0';

    if (start != text)
    {
        memmove(text, start, strlen(start) + 1);
    }
}

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
    while (table_name_length > 0 &&
       input[prefix_length + table_name_length - 1] == ' ')
    {
    table_name_length--;
    }

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

int parse_insert(
    const char *input,
    char *table_name,
    char *values
)
{
    const char *prefix = "INSERT INTO ";
    const char *values_keyword = " VALUES ";
    const char *values_start;
    const char *open_paren;
    const char *close_paren;

    size_t prefix_length;
    size_t table_name_length;
    size_t values_length;

    prefix_length = strlen(prefix);

    if (strncmp(input, prefix, prefix_length) != 0)
    {
        return 0;
    }

    values_keyword =
        strstr(input + prefix_length, " VALUES ");

    if (values_keyword == NULL)
    {
        return 0;
    }

    table_name_length =
        (size_t)(values_keyword -
                 (input + prefix_length));

    while (table_name_length > 0 &&
       input[prefix_length + table_name_length - 1] == ' ')
    {
    table_name_length--;
    }

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

    values_start =
        values_keyword + strlen(" VALUES ");

    open_paren = strchr(values_start, '(');
    close_paren = strrchr(values_start, ')');

    if (open_paren == NULL || close_paren == NULL)
    {
        return 0;
    }

    if (close_paren <= open_paren)
    {
        return 0;
    }

    values_length =
        (size_t)(close_paren - open_paren - 1);

    if (values_length == 0)
    {
        return 0;
    }

    strncpy(
        values,
        open_paren + 1,
        values_length
    );

    values[values_length] = '\0';

    return 1;
}

int parse_values(
    const char *values,
    const Table *table,
    Record *record
)
{
    int column_index = 0;
    int inside_quotes = 0;

    char token[64];
    int token_index = 0;

    for (int i = 0; ; i++)
    {
        char current = values[i];

        if (current == '"')
        {
            inside_quotes = !inside_quotes;
            continue;
        }

        if ((current == ',' && !inside_quotes) ||
            current == '\0')
        {
            token[token_index] = '\0';
	    trim_whitespace(token);

            if (column_index >= table->column_count)
            {
                return 0;
            }


            if (table->columns[column_index].type == TYPE_INT)
            {
                int value;

                if (sscanf(token, "%d", &value) != 1)
                {
                    return 0;
                }

                record->values[column_index].int_value = value;
            }
            else if (table->columns[column_index].type == TYPE_TEXT)
            {
                strncpy(
                    record->values[column_index].text_value,
                    token,
                    MAX_TEXT_LENGTH - 1
                );

                record->values[column_index]
                    .text_value[MAX_TEXT_LENGTH - 1] = '\0';
            }

            column_index++;
            token_index = 0;

            if (current == '\0')
            {
                break;
            }

            continue;
        }

        if (token_index < MAX_TEXT_LENGTH - 1)
        {
            token[token_index++] = current;
        }
        else
        {
            return 0;
        }
    }

    if (column_index != table->column_count)
    {
        return 0;
    }

    return 1;
}

int parse_select(
    const char *input,
    char *table_name,
    char *condition_column,
    char *condition_value
)
{
    const char *prefix = "SELECT * FROM ";
    const char *where_keyword = " WHERE ";

    const char *where_position;

    size_t prefix_length;
    size_t table_name_length;
    size_t condition_length;

    prefix_length = strlen(prefix);

    if (strncmp(input, prefix, prefix_length) != 0)
    {
        return 0;
    }

    where_position = strstr(
        input + prefix_length,
        where_keyword
    );

    /*
     * No WHERE clause:
     *
     * SELECT * FROM students
     */
    if (where_position == NULL)
    {
        table_name_length =
            strlen(input + prefix_length);

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

        condition_column[0] = '\0';
        condition_value[0] = '\0';

        return 1;
    }

    /*
     * WHERE exists:
     *
     * SELECT * FROM students WHERE age = 21
     */

    table_name_length =
        (size_t)(where_position -
                 (input + prefix_length));

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

    /*
     * Extract:
     *
     * age = 21
     */
    const char *condition =
        where_position + strlen(where_keyword);

    const char *equals =
        strchr(condition, '=');

    if (equals == NULL)
    {
        return 0;
    }

    /*
     * Extract column name.
     */
    size_t column_length =
        (size_t)(equals - condition);

    if (column_length == 0 ||
        column_length >= MAX_COLUMN_NAME_LENGTH)
    {
        return 0;
    }

    strncpy(
        condition_column,
        condition,
        column_length
    );

    condition_column[column_length] = '\0';

    trim_whitespace(condition_column);

    /*
     * Extract value.
     */
    const char *value =
        equals + 1;

    condition_length = strlen(value);

    if (condition_length == 0 ||
        condition_length >= MAX_TEXT_LENGTH)
    {
        return 0;
    }

    strncpy(
        condition_value,
        value,
        condition_length
    );

    condition_value[condition_length] = '\0';

    trim_whitespace(condition_value);

    /*
     * Remove surrounding quotes from TEXT values.
     */
    size_t value_length =
        strlen(condition_value);

    if (value_length >= 2 &&
        condition_value[0] == '"' &&
        condition_value[value_length - 1] == '"')
    {
        memmove(
            condition_value,
            condition_value + 1,
            value_length - 2
        );

        condition_value[value_length - 2] = '\0';
    }

    return 1;
}
