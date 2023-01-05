#ifndef _table
#define _table

#include "basic_lib_header.h"
#include "field.h"
#include "query.h"
#include "data.h"

class Table
{
public:
    std::string TableName;
    int DataNum;
    int FieldNum;
    std::map<std::string, Field> fieldMap;
    std::string pkName; //主键名 
    Data data;  // 数据
    std::string FieldPath; // 表对应的字段保存路径
    std::string DataPath;  // 表对应的数据保存路径
    std::vector<std::map<Key, Value>> DML_Select(Query);
    bool DML_Update(Query);
    bool DML_Insert(Query);
    bool DML_Delete(Query);
    bool addColumn(std::string, std::string, Field);
};


#endif