#ifndef STORAGE_H
#define STORAGE_H

#include "database.h"

#define DATABASE_FILE "data/database.db"

int save_database(const Database *database);
int load_database(Database *database);

#endif
