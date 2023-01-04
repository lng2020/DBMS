#ifndef _query
#define _query

#ifndef basic_lib_header
#include "basic_lib_header.h"
#endif

class Query;
class Condition;
typedef std::vector<std::string> Insert;
typedef std::vector<std::string> Field;
typedef std::map<std::string, std::string> Update;
typedef std::map<std::string, std::string> Aliase;


enum Type
{
    SELECT,
    INSERT,
    UPDATE,
    DELETE
};

class Condition
{
public:
    std::string op1;
    bool op1IsField;
    std::string op2;
    bool op2IsField;
};

class Query
{
public:
    Type type=SELECT;
    std::string tableName;
    std::vector<Condition> conditions;
    std::vector<Update> updates;
    std::vector<Insert> inserts;
    std::vector<Field> fields;
    std::vector<Aliase> aliases;
};

#endif