#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "database.h"

void execute_select(
    Database *database,
    const char *table_name,
    const char *condition_column,
    const char *condition_value
);

#endif
