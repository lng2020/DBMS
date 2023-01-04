#include "table.h"

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
    //利用条件筛选，返回一个record的vector
    //对vector进行投影操作，返回投影后的vector
};

bool Table::Insert(Query query){
    //如果有fieldName是主键
        //若主键重复，则报错
        //若主键无重复，生成一个record，插进data中

    //如果没有fieldName是主键，那就分配一个主键
        //生成一个record，插进data中
};

bool Table::Delete(Query query){
    //利用条件筛选，若不存在满足的记录，直接返回
    //若存在记录，将这些记录删除
}

bool Table::Update(Query query){
    //利用条件筛选，若不存在满足的记录，直接返回
    //若存在记录，生成一个更新后数据的记录vector，先调用Insert，再调用Delete
}