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

};

bool Table::Insert(Query query){
    
};

