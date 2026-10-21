#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "record.h"

int main(void)
{
    char table_name[MAX_TABLE_NAME_LENGTH];
    char condition_column[MAX_COLUMN_NAME_LENGTH];
    char condition_value[MAX_TEXT_LENGTH];
    char input[256];

    /* Normal DELETE query should be accepted. */
    strcpy(input, "DELETE FROM students WHERE id = 2");

    if (!parse_delete(input, table_name,
                      condition_column, condition_value))
    {
        printf("FAIL: Normal DELETE rejected\n");
        return 1;
    }

    printf("PASS: Normal DELETE accepted\n");

    /* Oversized condition value should be rejected. */
    strcpy(input, "DELETE FROM students WHERE id = ");
    memset(input + strlen(input), 'A',
           sizeof(input) - strlen(input) - 1);
    input[sizeof(input) - 1] = '\0';

    if (parse_delete(input, table_name,
                     condition_column, condition_value))
    {
        printf("FAIL: Oversized DELETE value accepted\n");
        return 1;
    }

    printf("PASS: Oversized DELETE value rejected\n");
    return 0;
}
