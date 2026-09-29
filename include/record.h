#ifndef RECORD_H
#define RECORD_H

#define MAX_TEXT_LENGTH 64

typedef union
{
    int int_value;
    char text_value[MAX_TEXT_LENGTH];
} Value;

typedef struct
{
    Value values[32];
} Record;

void init_record(Record *record);

#endif
