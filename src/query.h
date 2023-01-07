#ifndef _query
#define _query

#include "basic_lib_header.h"

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

class Condition //默认是 = 操作
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
    std::vector<Condition> conditions;// where语句后面的条件
    std::map<Key, Value> updates; //更新键值对的map
    std::vector<Insert> inserts; // vector，包含插入的记录--一些键值对组成的map
    std::vector<std::string> fieldNames; // field name
};

//解析sql语句
void judge(std::string str[]);

//转大写
std::string toUpper(std::string);

#endif