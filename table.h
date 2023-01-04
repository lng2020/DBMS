#ifndef _table
#define _table

#include "basic_lib_header.h"
#include "field.h"
#include "query.h"

class Table
{
public:
    std::string TableName;
    int DataNum;
    int FieldNum;
    Field *PFieldHead;
    Field *PFieldTail;
    std::string FieldPath; // 表对应的字段保存路径
    std::string DataPath;  // 表对应的数据保存路径
    bool DML(Query); //返回值是操作是否正确
    bool Select(Query);
    bool Update(Query);
    bool Insert(Query);
    bool Delete(Query);
    bool addColumn(std::string, std::string, Field);
};


#endif