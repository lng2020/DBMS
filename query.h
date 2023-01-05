#ifndef _query
#define _query

#ifndef basic_lib_header
#include "basic_lib_header.h"
#endif

class Query;
class Condition;
typedef std::string Key;
typedef std::string Value;
typedef std::map<Key, Value> Insert;


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
    Type type;
    std::string tableName;
    std::vector<Condition> conditions;
    std::map<Key, Value> updates;
    std::vector<Insert> inserts;
    std::vector<std::string> fieldNames;
};

//解析sql语句
void judge(std::string str[]);

//转大写
std::string toUpper(std::string x)
{
    std::transform(x.begin(), x.end(), x.begin(), ::toupper); //转大写
    return x;
}


#endif