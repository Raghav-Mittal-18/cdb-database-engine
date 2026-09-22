#include <stdio.h>
#include "table.h"

int main(void)
{
    Table table = create_table("students");

    printf("Table name: %s\n", table.name);

    return 0;
}
