#ifndef DATABASE_H
#define DATABASE_H

#include "table.h"

#define MAX_TABLES 100

typedef struct
{
    Table tables[MAX_TABLES];
    int table_count;
} Database;

void init_database(Database *database);
int add_table(Database *database, const char *table_name);
void print_database(const Database *database);

#endif
