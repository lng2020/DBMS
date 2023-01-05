#include "table.h"
#include <fstream>
#include <iostream>
using namespace std;

bool Table::DML(Query query)
{
    switch (query.type)
    {
    case SELECT:
        return Select(query);
    case UPDATE:
        return Update(query);
    case DELETE:
        return Delete(query);
    case INSERT:
        return Insert(query);
    default:
        return false;
    }
};

bool Table::Select(Query query){
    // 利用条件筛选，返回一个record的vector
    // 对vector进行投影操作，返回投影后的vector
};

bool Table::Insert(Query query){
    // 如果有fieldName是主键
    // 若主键重复，则报错
    // 若主键无重复，生成一个record，插进data中

    // 如果没有fieldName是主键，那就分配一个主键
    // 生成一个record，插进data中
};

bool Table::Delete(Query query)
{
    // 利用条件筛选，若不存在满足的记录，直接返回
    // 若存在记录，将这些记录删除
}

bool Table::Update(Query query)
{
    // 利用条件筛选，若不存在满足的记录，直接返回
    // 若存在记录，生成一个更新后数据的记录vector，先调用Insert，再调用Delete
}

void Table::loadField()
{
    ifstream infile;
    infile.open(this->FieldPath, ios::in);

    while (!infile.eof())
    {
        Field temp;
        string str;
        getline(infile, str);
        // 转换成C中的char*
        char *cstr = new char[str.length() + 1]; // 首行读入
        strcpy_s(cstr, str.length() + 1, str.c_str());
        // 通过,进行分割
        const char *seps = ",";
        char *token = NULL;
        temp.FieldName = strtok(cstr, seps);
        temp.FieldType = strtok(NULL, seps);
        temp.Size = stoi(strtok(NULL, seps));
        temp.Key = bool(stoi(strtok(NULL, seps)));
        temp.NullFlag = bool(stoi(strtok(NULL, seps)));
        temp.ValidFlag = bool(stoi(strtok(NULL, seps)));
        this->fieldMap[temp.FieldName] = temp;
        if(temp.Key) this->pkName = temp.FieldName;
    }
}