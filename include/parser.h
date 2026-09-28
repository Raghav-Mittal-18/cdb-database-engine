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

#endif
