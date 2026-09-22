#ifndef TABLE_H
#define TABLE_H

#define MAX_TABLE_NAME_LENGTH 64

typedef struct
{
    char name[MAX_TABLE_NAME_LENGTH];
} Table;

Table create_table(const char *name);
#endif
