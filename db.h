#ifndef basic_lib_header
#include "basic_lib_header.h"
#endif

#include "field.h"
#include "table.h"

int createDatabase(std::string);
int create(std::string, std::string, std::vector<Field>);
int dropTable(std::string, std::string );
int renameTable(std::string, std::string, std::string);