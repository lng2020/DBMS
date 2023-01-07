#ifndef _table
#define _table

#include "basic_lib_header.h"
#include "field.h"
#include "query.h"
#include "bplustree.h"
#include "storage.h"

class Table
{
public:
    Table(std::string);
    std::string TableName;
    int DataNum;
    int FieldNum;
    std::map<std::string, Field> fieldMap;
    std::string pkName; //主键名 
    BPlusTree data;  // 数据
    Storage storage; // db文件在内存中抽象，相当于将db文件整个加载进storage这片内存中
    std::string FieldPath; // 表对应的字段保存路径
    std::string DataPath;  // 表对应的数据保存路径
    std::vector<std::map<Key, Value>> DML_Select(Query);
    bool DML_Update(Query);
    bool DML_Insert(Query);
    bool DML_Delete(Query);
    bool addColumn(std::string, std::string, Field);
    void loadField(); //加载fieldMap和pkName
    void loadData(); //加载Data
};


#endif