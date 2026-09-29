#include "record.h"
#include <string.h>

void init_record(Record *record)
{
    for (int i = 0; i < 32; i++)
    {
        record->values[i].int_value = 0;
        record->values[i].text_value[0] = '\0';
    }
}
