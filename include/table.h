#ifndef TABLE_H
#define TABLE_H

#define MAX_TABLE_NAME_LENGTH 64
#define MAX_COLUMNS 32
#define MAX_COLUMN_NAME_LENGTH 64

typedef enum
{
    TYPE_INT,
    TYPE_TEXT
} DataType;

typedef struct
{
    char name[MAX_COLUMN_NAME_LENGTH];
    DataType type;
} Column;

typedef struct
{
    char name[MAX_TABLE_NAME_LENGTH];

    Column columns[MAX_COLUMNS];

    int column_count;
    int record_count;
} Table;

Table create_table(const char *name);
int add_column(Table *table, const char *column_name, DataType type);
const char *data_type_to_string(DataType type);
void print_table(const Table *table);

#endif
