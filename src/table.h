#ifndef _table
#define _table

#include "basic_lib_header.h"
#include "field.h"
#include "bplustree.h"
#include "storage.h"

typedef std::string Value;
typedef std::string Key;

class Table
{
public:
    Table(std::string);
    std::string TableName;
    int DataNum;
    int FieldNum;
    std::vector<Field> fields;
    std::string pkName; //主键名 
    BPlusTree data;  // 数据
    Storage storage; // db文件在内存中抽象，相当于将db文件整个加载进storage这片内存中
    std::string FieldPath; // 表对应的字段保存路径
    std::string DataPath;  // 表对应的数据保存路径
    std::vector<std::map<Key, Value>> DML_Select(std::string);
    bool DML_Update(std::vector<std::string>);
    bool DML_Insert(std::vector<std::string>);
    bool DML_Delete(std::string);
    bool addColumn(std::string, std::string, Field);
    void loadField(); //加载fieldMap和pkName
    void loadData(); //加载Data
};


#endif