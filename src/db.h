#ifndef _db
#define _db

#include "field.h"
#include "table.h"

bool createDatabase(std::string);
bool dropDatabase(std::string);
Table createTable(std::string, std::string, std::vector<Field>);
bool dropTable(std::string, std::string);
bool renameTable(std::string, std::string, std::string);
Table readTable(std::string, std::string);

#endif