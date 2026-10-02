#ifndef PARSER_H
#define PARSER_H

#include "table.h"

int parse_create_table(
    const char *input,
    char *table_name
);

int extract_column_definitions(
    const char *input,
    char *column_definitions
);

int parse_column_definitions(
    const char *column_definitions,
    Table *table
);

int parse_insert(
    const char *input,
    char *table_name,
    char *values
);

int parse_values(
    const char *values,
    const Table *table,
    Record *record
);

int parse_select(
    const char *input,
    char *table_name,
    char *condition_column,
    char *condition_value
);

int parse_update(
    const char *input,
    char *table_name,
    char *set_column,
    char *set_value,
    char *condition_column,
    char *condition_value
);

#endif
