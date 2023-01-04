#ifndef _table
#define _table

#include "basic_lib_header.h"
#include "field.h"
#include "query.h"

class table
{
public:
    std::string TableName;
    int DataNum;
    int FieldNum;
    Field *PFieldHead;
    Field *PFieldTail;
    std::string FieldPath; // 表对应的字段保存路径
    std::string DataPath;  // 表对应的数据保存路径
    bool DML(Query);
};

#endif