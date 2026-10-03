#include "storage.h"
#include <stdio.h>

int save_database(const Database *database)
{
    FILE *file = fopen(DATABASE_FILE, "wb");

    if (file == NULL)
    {
        return 0;
    }

    size_t written = fwrite(
        database,
        sizeof(Database),
        1,
        file
    );

    fclose(file);

    if (written != 1)
    {
        return 0;
    }

    return 1;
}


int load_database(Database *database)
{
    FILE *file = fopen(DATABASE_FILE, "rb");

    if (file == NULL)
    {
        return 0;
    }

    size_t read = fread(
        database,
        sizeof(Database),
        1,
        file
    );

    fclose(file);

    if (read != 1)
    {
        return 0;
    }

    return 1;
}
