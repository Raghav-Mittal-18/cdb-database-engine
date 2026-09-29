#include "database.h"
#include <stdio.h>
#include <string.h>

void init_database(Database *database)
{
    database->table_count = 0;
}

int add_table(Database *database, const char *table_name)
{
    if (database->table_count >= MAX_TABLES)
    {
        return 0;
    }

    database->tables[database->table_count] = create_table(table_name);
    database->table_count++;

    return 1;
}

Table *get_table(Database *database, const char *table_name)
{
    for (int i = 0; i < database->table_count; i++)
    {
        if (strcmp(database->tables[i].name, table_name) == 0)
        {
            return &database->tables[i];
        }
    }

    return NULL;
}

void print_database(const Database *database)
{
    printf("Database contains %d table(s):\n",
           database->table_count);

    for (int i = 0; i < database->table_count; i++)
    {
        printf("%d. %s\n",
               i + 1,
               database->tables[i].name);
	print_table(&database->tables[i]);
    }
}
