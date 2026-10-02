#ifndef EXECUTOR_H
#define EXECUTOR_H

#include "database.h"

void execute_select(
    Database *database,
    const char *table_name,
    const char *condition_column,
    const char *condition_value
);

void execute_update(
    Database *database,
    const char *table_name,
    const char *set_column,
    const char *set_value,
    const char *condition_column,
    const char *condition_value
);

#endif
