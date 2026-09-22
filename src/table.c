#include "table.h"
#include <string.h>

Table create_table(const char *name)
{
    Table table;

    strncpy(table.name, name, MAX_TABLE_NAME_LENGTH - 1);
    table.name[MAX_TABLE_NAME_LENGTH - 1] = '\0';

    return table;
}
